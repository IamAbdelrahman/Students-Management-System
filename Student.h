/******************************************************************************
 * Copyright (C) 2023 by Abdelrahman Kamal - Learn-In-Depth
 *****************************************************************************/
/**
 * @file Student.h
 * @brief Interface of Queue data structures.
 *
 * @author Abdelrahman Kamal
 * @date 25/09/2023
 *
 */
#ifndef STUDENT_H_
#define STUDENT_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "ctype.h"
#define PRINT(...)           \
    {                        \
        fflush(stdout);      \
        fflush(stdin);       \
        printf(__VA_ARGS__); \
        fflush(stdout);      \
        fflush(stdin);       \
    }

typedef struct studen_info
{
    char fname[51];
    char lname[51];
    int roll;
    float GPA;
    int cid[10];
} QUEUEENTRY;

typedef struct queuenode
{
    QUEUEENTRY student;
    struct queuenode *next;
} QueueNode_t;

typedef struct queue
{
    QueueNode_t *front;
    QueueNode_t *rear;
    int size;
} Queue_t;

typedef enum student_state
{
    STUDENT_STATE_INIT,
    STUDENT_STATE_ADD,
    STUDENT_STATE_DELETE,
    STUDENT_STATE_EMPTY,
    STUDENT_STATE_CLEAR,
    STUDENT_STATE_FIND,
    STUDENT_STATE_COUNT,
    STUDENT_STATE_UPDATE,
    STUDENT_STATE_DISPLAY,
    STUDENT_STATE_ERROR
} STUDENT_STATE_t;
/**
 * @brief  Intializing the Queue
 *
 *  This function is used to initialize the Queue through
 *  initializing front and rear pointers with NULL, and initializing
 *  the size with zero.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_INIT if the queue is initialized sucessfully.
 *         - STUDENT_STATE_ERROR if the queue was not created or declared
 */
STUDENT_STATE_t initializeQueue(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Add a student manaully.
 *
 * This function appends a new element at the rear of the queue.
 * It checks for memory availability and returns STUDENT_STATE_ERROR if memory is full.
 * Or if the operation fails.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_ADD if the student is added sucessfully.
 *         - STUDENT_STATE_ERROR if the dynamically allocation related to the new node failed
 *          , the queue was not created, or a roll number enterded by a the user is already existed before.
 */
STUDENT_STATE_t addStudentManually(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Add a student from a file.
 *
 * This function appends a new element at the rear of the queue.
 * It checks for memory availability and returns STUDENT_STATE_ERROR if memory is full.
 * Or if the operation fails.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_ADD if the student is added sucessfully.
 *         - STUDENT_STATE_ERROR if the file cannot be opened, if the dynamically allocation
 *          related to the new node failed, if the queue was not created, or a roll number entered
 *          by the user is already existed before.
 */
STUDENT_STATE_t addStudentFromFile(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief Find a Student by Roll Number
 *
 * This function searches for a student in a queue database based on their roll number.
 * It takes a pointer to the queue and a function pointer to perform an action on the found student.
 *
 * @param Pq A pointer to struct Queue
 * @param Pf A function pointer to a function that performs an action on the found student.
 *           This function is responsible for processing or displaying information about the student.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_FIND if the student with the specified roll number is found and processed.
 *         - STUDENT_STATE_ERROR if the queue is empty, if the specified roll number is not found
 *          , if the dynamically allocation related to the new node failed, or if the queue was not created.
 */
STUDENT_STATE_t findStudentRoll(Queue_t *, void (*)(QUEUEENTRY *));
/*-------------------------------------------------------------------------------------*/

/*
 * @brief Find a Student by First Name
 *
 * This function searches for students in a queue database based on their first name.
 * It takes a pointer to the queue and a function pointer to perform an action on the found student.
 *
 * @param Pq A pointer to struct Queue
 * @param Pf A function pointer to a function that performs an action on the found student.
 *           This function is responsible for processing or displaying information about the student.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_FIND if the student with the specified first name is found and processed.
 *         - STUDENT_STATE_ERROR if the queue is empty, if the specified first name is not found
 *          , if the dynamically allocation related to the new node failed, or if the queue was not created.
 */
STUDENT_STATE_t findStudentFname(Queue_t *, void (*)(QUEUEENTRY *));
/*-------------------------------------------------------------------------------------*/

/**
 * @brief Find a Student by a Course Registered
 *
 * This function searches for students in a queue database based on their regisertaion in a course.
 * It takes a pointer to the queue and a function pointer to perform an action on the found student.
 *
 * @param Pq A pointer to struct Queue
 * @param Pf A function pointer to a function that performs an action on the found student.
 *           This function is responsible for processing or displaying information about the student.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_FIND if the student with the specified registered course is found and processed.
 *         - STUDENT_STATE_ERROR if the queue is empty, if the specified course ID is not found
 *          , if the dynamically allocation related to the new node failed, or if the queue was not created.
 */
STUDENT_STATE_t findStudentCouseId(Queue_t *, void (*)(QUEUEENTRY *));
/*-------------------------------------------------------------------------------------*/

/**
 * @brief Delete a Student by Roll Number
 *
 * This function searches for a student in a queue database based on their roll number.
 * Then deletes the student, if it doesn't find the roll number it returns an error state.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_DELETE if the student with the specified roll number is found and deleted.
 *         - STUDENT_STATE_ERROR if the queue is empty, if the specified roll number is not found
 *          , if the dynamically allocation related to the new node failed, or if the queue was not created.
 */
STUDENT_STATE_t deleteStudentRoll(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief Update a student
 *
 * This function searches for a student in a queue database based on their roll number.
 * Then updates the student details, if it doesn't find the roll number it returns an error state.
 *
 * @param Pq A pointer to a struct Queue.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_UPDATE if the student with the specified roll number is found and updated.
 *         - STUDENT_STATE_ERROR if the queue is empty, if the specified roll number is not found
 *          , if the dynamically allocation related to the new node failed, or if the queue was not created.
 */
STUDENT_STATE_t updateStudent(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Get the Queue Size.
 *
 * This function gets the size of the queue of students by checking the value
 * of the size variable in the queue datastructure.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_COUNT if the queue has students.
 *         - STUDENT_STATE_ERROR if the queue was not created.
 */
STUDENT_STATE_t countStudent(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Show information of students.
 *
 *  This function traversed all the student members in the queue database and performs an action
 *  on each member using a function passed to it.
 *
 * @param Pq A pointer to struct Queue
 * @param Pf A function pointer to a function that performs an action on the found student.
 *           This function is responsible for processing or displaying information about the student.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_DISPLAY if the queue has students.
 *         - STUDENT_STATE_ERROR if the queue was not created, if the dynamically allocation related to
 *         the node failed, or if the queue is empty
 */
STUDENT_STATE_t showStudent(Queue_t *, void (*)(QUEUEENTRY *));
/*-------------------------------------------------------------------------------------*/

/**
 * @brief Delete all students
 *
 * This function clears the queue database through initializing the front and the rear pointers
 * to NULL, and the size with zero. Just as the initialization process.
 *
 * @param Pq A pointer to a struct Queue.
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_DELETE if the queue has been deleted successfully.
 *         - STUDENT_STATE_ERROR if the queue was not created, or if the queue is empty.
 */
STUDENT_STATE_t deleteAllStudents(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Check if the queue is empty.
 *
 * This function checks if the queue is empty or not by checking
 * the front pointer if it points to NULL or not
 *
 * @param Pq A pointer to struct Queue
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_EMPTY if the queue is empty.
 *         - STUDENT_STATE_ERROR if the queue was not created.
 */
STUDENT_STATE_t IsQueueEmpty(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Check if the queue is full.
 *
 * This function checks if the queue is full. In practice, the queue
 * will not be full unless the user exceeds the size of the physical
 * (.stack) segment in RAM. It always returns 0.
 *
 * @param Pq A pointer to struct Queue
 *
 * @return Always returns 0.
 */
int IsQueueFull(Queue_t *);
/*-------------------------------------------------------------------------------------*/

/**
 * @brief  Check if Roll number exists.
 *
 * This function checks if the queue is full. In practice, the queue
 * will not be full unless the user exceeds the size of the physical
 * (.stack) segment in RAM. It always returns 0.
 *
 * @param Pq A pointer to struct Queue
 * @param roll An integer variable
 *
 * @return It returns one of the following values:
 *         - STUDENT_STATE_FIND if the roll number is already found.
 *         - STUDENT_STATE_ERROR if the queue was not created, if the queue is empty,
 *          or if the dynamically allocation related to a new node is failed.
 */
STUDENT_STATE_t checkRoll(Queue_t *, int);
/*-----------------------------------------------------------------------------------*/

#endif // !STUDENT_H_
