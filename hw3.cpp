#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

sem_t mutex;
sem_t dentistReady;
sem_t seatCountWriteAccess;
sem_t patientReady;

int numberOfFreeWRSeats = 0;

/*
 * Struct that will be passed through to keep track of the
 * patient number 
 */
struct patients_t {
    int patientNum;
};

void* Dentist(void* arg) {

    /* General print statements */
    string dentistAquiring = "Dentist trying to acquire patient…";
    string dentistAquiringSeat = "Dentist trying to acquire seatCountWriteAccess…";
    string dentistReadyConsult = "Dentist ready to consult…";
    string dentistReleasignSeats = "Dentist releasing seatCountWriteAccess…";
    string dentistConsulting = "Dentist consulting patient…";

    while(true) {
        //Get patient
        printf("%s\n", dentistAquiring.c_str());
        sem_wait(&patientReady);
        printf("%s\n", dentistAquiringSeat.c_str());
        sem_wait(&seatCountWriteAccess);

        //Add free seat
        numberOfFreeWRSeats += 1;
        string dentistIncrementing = "Incremented free seats to " 
            + to_string(numberOfFreeWRSeats);
        printf("%s\n", dentistIncrementing.c_str());
        //Ready to consult
        printf("%s\n", dentistReadyConsult.c_str());
        sem_post(&dentistReady);
        printf("%s\n", dentistReleasignSeats.c_str());
        sem_post(&seatCountWriteAccess);
        printf("%s\n", dentistConsulting.c_str());
        //Talking to patient
    }
    pthread_exit(0);
}

void* Customer(void* arg) {
    /* Converting Struct */
    struct patients_t *tempStruct = (struct patients_t*) arg;
    int threadID =  tempStruct->patientNum;
    
    while(true) {    
        //Waiting for a free seat
        string waitForSeat = "Customer " + to_string(threadID) 
            + " trying to acquire seatCountWriteAccess…";
        printf("%s\n", waitForSeat.c_str());
        sem_wait(&seatCountWriteAccess);

        //Free seats still left
        if(numberOfFreeWRSeats > 0) {
            //Remove 1 seat
            numberOfFreeWRSeats -= 1;
            string customerSeated = "Customer " + to_string(threadID) 
                + " seated; Remaining chairs=" + to_string(numberOfFreeWRSeats);
            printf("%s\n", customerSeated.c_str());
            string customerNotifyDentist = "Customer " + to_string(threadID) 
                + " notifying dentist patientReady…";
            printf("%s\n", customerNotifyDentist.c_str());
            sem_post(&patientReady);
            string customerReleaseSeat = "Customer " + to_string(threadID) 
                + " releasing seatCountWriteAccess…";
            printf("%s\n", customerReleaseSeat.c_str());
            sem_post(&seatCountWriteAccess);
            string customerWaitDentist = "Customer " + to_string(threadID) 
                + " waiting for dentist…";
            printf("%s\n", customerWaitDentist.c_str());
            sem_wait(&dentistReady);
            string customerConsulting = "Customer " + to_string(threadID) 
                + " consulting dentist…";
            printf("%s\n", customerConsulting.c_str());
        }
        //No free seats
        else {
            string customerLeaving = "Customer " + to_string(threadID) 
                + " leaving without consulting; no chairs available…";
            printf("%s\n", customerLeaving.c_str());
            sem_post(&seatCountWriteAccess);
            //Leave without consulting
        }
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    //Create Sempahores
    sem_init(&dentistReady, 0, 1);
    sem_init(&seatCountWriteAccess, 0, 1);
    sem_init(&patientReady, 0, 1);
    
    /* Convert command line arguements to work with program */
    stringstream stream(argv[1]);
    stream >> numberOfFreeWRSeats;
    stringstream stream2(argv[2]);
    int argInput2 = 0;
    stream2 >> argInput2;
    const int PATIENT_THREAD_NUM = argInput2;

    /* Create Threads */
    pthread_t *thread = new pthread_t[PATIENT_THREAD_NUM];
    pthread_t dentistThread;

    /* Create Dentist Thread */
    int status = pthread_create(&dentistThread, NULL, Dentist, NULL);
    if(status) {
        string denErr = "Error when creating dentist thread";
        printf("%s\n", denErr.c_str());
        exit(1);
    }

    /* Create Patient Threads */
    for(int i=0; i < PATIENT_THREAD_NUM; i++) {
        /* Dynamic allocation of struct to pass data */
        struct patients_t *tempStruct = new struct patients_t;
        tempStruct->patientNum = i;

        /*  Pass struct through threads */
        int status = pthread_create(&thread[i], NULL, Customer, (void*) tempStruct);

        /* If there is an error in creating a thread, exit */
        if(status) {
            string err = "Error when creating patient thread #" + (to_string(i));
            printf("%s\n", err.c_str());
            exit(1);
        }

    }

    /* Join all the threads */
    for(int i=0; i < PATIENT_THREAD_NUM; i++) {
        pthread_join(thread[i], NULL);
    }
    pthread_join(dentistThread, NULL);
    
    /* Destroy Semaphores */
    sem_destroy(&dentistReady);
    sem_destroy(&seatCountWriteAccess);
    sem_destroy(&patientReady);

    return 0;
}
