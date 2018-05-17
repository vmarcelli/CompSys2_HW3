#include <semaphore.h>
#include <pthread.h>
#include <iostream>

using namespace std;

sem_t mutex;
sem_t dentistReady;
sem_t seatCountWriteAccess;
sem_t patientReady;

int numberOfFreeWRSeats = 0;

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
    int threadID =  pthread_self();

    while(true) {
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

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread, NULL);

    pthread_create(&t2, NULL, thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&mutex);


    return 0;
}
