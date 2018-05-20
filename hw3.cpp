#include <semaphore.h>
#include <pthread.h>
#include <iostream>

using namespace std;

sem_t mutex;
sem_t dentistReady;
sem_t seatCountWriteAccess;
sem_t patientReady;

int numberOfFreeWRSeats = 0;

struct patients {
    int patientNum;
};

void* Dentist(void* arg) {

    while(true) {
        cout << "Dentist trying to acquire patient…" << endl;
        sem_wait(&patientReady);
        cout << "Dentist trying to acquire seatCountWriteAccess…" << endl;

        sem_wait(&seatCountWriteAccess);
        if(numberOfFreeWRSeats > 0) {
            numberOfFreeWRSeats += 1;
            cout << "Incremented free seats to " << numberOfFreeWRSeats << endl;

            sem_post(&patientReady);
            cout << "“Dentist releasing seatCountWriteAccess…" << endl;
            sem_post(&seatCountWriteAccess);
            cout << "Dentist consulting patient…" << endl;
            sem_wait(&dentistReady);

        }
        else {
            cout << "“Dentist releasing seatCountWriteAccess…" << endl;
            sem_post(&seatCountWriteAccess);
            cout << "Dentist consulting patient…" << endl;
        }
    }

}

void* Customer(void * arg) {
    struct patients *tempStruct = (struct patients) ptr;
    int threadID =  tempStruct->patientNum;

    while(true) {
        //Waitinf for a free seat
        cout << "“Customer " << threadID << "trying to acquire seatCountWriteAccess…" << endl;
        sem_wait(&seatCountWriteAccess);

        if(numberOfFreeWRSeats > 0) {
            numberOfFreeWRSeats -= 1;
            cout << "“Customer " << threadID << " seated; Remaining chairs=" << numberOfFreeWRSeats << endl;
            cout << "Customer " << threadID << " notifying dentist patientReady…" << endl;
            sem_post(&patientReady);
            cout << "Customer " << threadID << " releasing seatCountWriteAccess…" << endl;
            sem_post(&seatCountWriteAccess);
            cout << "Customer " << threadID << " waiting for dentist…" << endl;
            sem_wait(&dentistReady);
            cout << "Customer " << threadID << " consulting dentist…" << endl;

        }
        //No free seats
        else {
            cout << "Customer " << threadID << " leaving without consulting; no chairs available…" << endl;
            sem_post(&seatCountWriteAccess);
            //Leave without consulting
        }

    }

}
void* thread(void* arg) {
    int threadID =  pthread_self();

    //waiting
    sem_wait(&mutex);
    cout << "Inside of thread" << endl;

    //critical section
    cout << "Doing critical stuff " << threadID << endl;

    //signal
    cout << "Exiting thread" << endl;
    sem_post(&mutex);

}

int main() {
    sem_init(&mutex, 0 , 1);
    sem_init(&dentistReady, 0, 1);
    sem_init(&seatCountWriteAccess, 0, 1);
    sem_init(&patientReady, 0, 1);
    numberOfFreeWRSeats = 5;
    int PATIENT_THREAD_NUM = 5;

    pthread_t thread[PATIENT_THREAD_NUM];

    for(int i=0; i < PATIENT_THREAD_NUM; i++) {
        /* Dynamic allocation of struct to pass data */
        struct patients *tempStruct = new struct patients;
        tempStruct->patientNum = i;

        /*  Pass struct through threads */
        int status = pthread_create(&thread[i], NULL, Customer, (void*) tempStruct);

        /* If there is an error in creating a thread, exit */
        if(status) {
            string err = "Error when creating thread #" + (to_string(i));
            printf("\n"err"\n");
            exit(1);
        }

    }

    /* Join all the threads */
    for(int i=0; i < PATIENT_THREAD_NUM; i++) {
        pthread_join(thread[i], NULL);
    }
    
    sem_destroy(&mutex);


    return 0;
}
