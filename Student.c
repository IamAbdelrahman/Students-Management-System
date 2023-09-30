/******************************************************************************
 * Copyright (C) 2023 by Abdelrahman Kamal - Learn-In-Depth
 *****************************************************************************/
/**
 * @file Student.c
 * @brief Implementaion of Queue Data Structure
 *
 * @author Abdelrahman Kamal
 * @date 25/9/2023
 *
 */
#include "Student.h"

STUDENT_STATE_t initializeQueue(Queue_t *Pq)
{
    if (Pq)
    {
        Pq->front = NULL;
        Pq->rear = NULL;
        Pq->size = 0;
        return STUDENT_STATE_INIT;
    }
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t addStudentManually(Queue_t *Pq)
{
    QueueNode_t *Ps = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (!Ps || !Pq)
    {   
        return STUDENT_STATE_ERROR;
    }
    else
    {
        PRINT("Enter the Roll Number: ");
        scanf("%d", &Ps->student.roll);
        if (checkRoll(Pq, Ps->student.roll) == STUDENT_STATE_FIND)
        {
            PRINT("[ERROR] Roll number %d already exists\n", Ps->student.roll);
            return STUDENT_STATE_ERROR;
        }
        PRINT("Enter the first name of student: ");
        scanf("%s", Ps->student.fname);
        PRINT("Enter the last name of student: ");
        scanf("%s", Ps->student.lname);
        PRINT("Enter the GPA you obtained: ");
        scanf("%f", &Ps->student.GPA);
        PRINT("Enter the course ID of each course\n");
        int i = 0;
        for (i = 0; i < 5; i++)
        {
            PRINT("Course %d id: ", i + 1);
            scanf("%d", &Ps->student.cid[i]);
        }
        Ps->next = NULL;
    }
    if (!Pq->rear)
    {
        Pq->front = Ps;
    }
    else
    {
        Pq->rear->next = Ps;
    }
    Pq->rear = Ps;
    Pq->size++;

    PRINT("[INFO] Student Details is added Successfully\n");
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ADD;
}

STUDENT_STATE_t addStudentFromFile(Queue_t *Pq)
{
    if (!Pq)
    {
        return STUDENT_STATE_ERROR;
    }
    FILE *ifp;
    char ch[500];
    ifp = fopen("Student_Info.txt", "r");
    if (!ifp)
    {
        printf("[ERROR] Cannot open the file\n");
        return STUDENT_STATE_ERROR;
    }
    else
    {
        while (fgets(ch, 500, ifp) != NULL)
        {
            QueueNode_t *Ps = (QueueNode_t *)malloc(sizeof(QueueNode_t));
            if (!Ps)
            {
                return STUDENT_STATE_ERROR;
            }
            sscanf(ch, "%s %s %d %f %d %d %d %d %d", Ps->student.fname,
                   Ps->student.lname, &Ps->student.roll, &Ps->student.GPA,
                   &Ps->student.cid[0], &Ps->student.cid[1], &Ps->student.cid[2],
                   &Ps->student.cid[3], &Ps->student.cid[4]);
            if (checkRoll(Pq, Ps->student.roll) == STUDENT_STATE_FIND)
            {
                PRINT("[ERROR] Roll number %d already exists\n", Ps->student.roll);
                return STUDENT_STATE_ERROR;
            }
            Ps->next = NULL;
            if (!Pq->rear)
            {
                Pq->front = Ps;
            }
            else
            {
                Pq->rear->next = Ps;
            }
            Pq->rear = Ps;
            Pq->size++;
        }
        fclose(ifp);
    }

    PRINT("[INFO] Student Details is added Successfully\n");
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ADD;
}

STUDENT_STATE_t findStudentRoll(Queue_t *Pq, void (*Pf)(QUEUEENTRY *Ps))
{
    QueueNode_t *Rn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Rn || !Pq)
    {
        return STUDENT_STATE_ERROR;
    }
    Rn = Pq->front;
    int roll;
    PRINT("Enter the roll number: ");
    scanf("%d", &roll);
    if (roll == Rn->student.roll)
    {
        (*Pf)(&Rn->student);
        return STUDENT_STATE_FIND;
    }
    while (Rn->next)
    {
        if (roll == Rn->next->student.roll)
        {
            (*Pf)(&Rn->next->student);
            return STUDENT_STATE_FIND;
        }
        Rn = Rn->next;
    }
    PRINT("[ERROR] Roll number %d is not found\n", roll);
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t findStudentFname(Queue_t *Pq, void (*Pf)(QUEUEENTRY *Ps))
{
    QueueNode_t *Fn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq || !Fn)
    {
        return STUDENT_STATE_ERROR;
    }
    Fn = Pq->front;
    char fName[51];
    PRINT("Enter the first name: ");
    scanf("%s", fName);
    while (Fn)
    {
        if (strcmp(fName, Fn->student.fname) == 0)
        {
            (*Pf)(&Fn->student);
            return STUDENT_STATE_FIND;
        }
        Fn = Fn->next;
    }
    PRINT("[ERROR] First Name %s is not found\n", fName);
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t findStudentCouseId(Queue_t *Pq, void (*Pf)(QUEUEENTRY *Ps))
{
    QueueNode_t *Cn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Cn || !Pq)
    {
        return STUDENT_STATE_ERROR;
    }
    Cn = Pq->front;
    int id = 0, i = 0, count = 0;
    PRINT("Enter the course ID: ");
    scanf("%d", &id);
    while (Cn)
    {
        for (i = 0; i < 5; i++)
        {
            if (id == Cn->student.cid[i])
            {
                (*Pf)(&Cn->student);
                count++;
            }
        }
        Cn = Cn->next;
        i = 0;
    }
    if (count)
    {
        return STUDENT_STATE_FIND;
    }
    PRINT("[ERROR] Course ID %d is not found\n", id);
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t deleteStudentRoll(Queue_t *Pq)
{
    QueueNode_t *temp = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq || !temp)
    {
        return STUDENT_STATE_ERROR;
    }
    int roll;
    PRINT("Enter the roll number: ");
    scanf("%d", &roll);
    if (roll == Pq->front->student.roll)
    {
        temp = Pq->front;
        Pq->front = Pq->front->next;
        free(temp);
        if (!Pq->front)
        {
            Pq->rear = NULL;
        }
        Pq->size--;
        PRINT("The Roll Number %d is removed successfully\n", roll);
        PRINT("-----------------------------------------\n");
        return STUDENT_STATE_DELETE;
    }
    else if (roll == Pq->rear->student.roll)
    {
        temp = Pq->front;
        int i = 0;
        for (i = 0; i < Pq->size - 2; i++)
        {
            temp = temp->next;
        }
        temp->next = Pq->rear->next;
        free(Pq->rear);
        Pq->rear = temp;
        Pq->size--;
        PRINT("The Roll Number %d is removed successfully\n", roll);
        PRINT("-----------------------------------------\n");
        return STUDENT_STATE_DELETE;
    }
    QueueNode_t *Dn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (!Dn)
    {
        return STUDENT_STATE_ERROR;
    }
    Dn = Pq->front;
    while (Dn->next)
    {
        if (roll == Dn->next->student.roll)
        {
            QueueNode_t *temp = Dn->next;
            Dn->next = Dn->next->next;
            free(temp);
            Pq->size--;
            PRINT("The Roll Number %d is removed successfully\n", roll);
            PRINT("-----------------------------------------\n");
            return STUDENT_STATE_DELETE;
        }
        Dn = Dn->next;
    }
    PRINT("[ERROR] Roll number %d is not found\n", roll);
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t updateStudent(Queue_t *Pq)
{
    QueueNode_t *Rn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq || !Rn)
    {
        return STUDENT_STATE_ERROR;
    }
    PRINT("Enter the roll number to update the entry: ");
    int roll = 0;
    scanf("%d", &roll);
    int i = 0;
    Rn = Pq->front;
    while (Rn)
    {
        if (roll == Rn->student.roll)
        {
            int order = 0;
            PRINT("1. First Name\n");
            PRINT("2. Last Name\n");
            PRINT("3. Roll Number\n");
            PRINT("4. GPA\n");
            PRINT("5. Courses\n");
            PRINT(": ");
            scanf("%d", &order);
            switch (order)
            {
            case 1:
                PRINT("Enter the new first name: ");
                scanf("%s", Rn->student.fname);
                break;
            case 2:
                PRINT("Enter the new last name: ");
                scanf("%s", Rn->student.lname);
                break;
            case 3:
                PRINT("Enter the new roll number: ");
                scanf("%d", &Rn->student.roll);
                break;
            case 4:
                PRINT("Enter the new GPA: ");
                scanf("%f", &Rn->student.GPA);
                break;
            case 5:
                PRINT("Enter the new courses id: ");
                int i = 0;
                for (i = 0; i < 5; i++)
                {
                    PRINT("Course %d ID: ", i + 1);
                    scanf("%d", &Rn->student.cid[i]);
                }
                break;
            default:
                break;
            }
            PRINT("[INFO] UPDATED SUCCESSFULLY\n");
            PRINT("-----------------------------------------\n");
            return STUDENT_STATE_UPDATE;
        }
        Rn = Rn->next;
    }
    PRINT("[ERROR] Roll number %d is not found\n", roll);
    PRINT("-----------------------------------------\n");
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t countStudent(Queue_t *Pq)
{
    if (Pq)
    {
        PRINT("The total number of students is %d\n", Pq->size);
        PRINT("You can add up to 50 Students\n");
        PRINT("You can add %d more Students\n", 50 - Pq->size);
        PRINT("-----------------------------------------\n");
        return STUDENT_STATE_COUNT;
    }
    return STUDENT_STATE_ERROR;
}

STUDENT_STATE_t showStudent(Queue_t *Pq, void (*Pf)(QUEUEENTRY *PStudent))
{
    QueueNode_t *Ps = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq || !Ps)
    {
        return STUDENT_STATE_ERROR;
    }

    Ps = Pq->front;
    for (Ps = Pq->front; Ps; Ps = Ps->next)
    {
        (*Pf)(&Ps->student);
    }
    return STUDENT_STATE_DISPLAY;
}

STUDENT_STATE_t deleteAllStudents(Queue_t *Pq)
{
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq)
    {
        return STUDENT_STATE_ERROR;
    }
    while (Pq->front)
    {
        Pq->rear = Pq->front->next;
        free(Pq->front);
        Pq->front = Pq->rear;
    }
    Pq->size = 0;
    return STUDENT_STATE_CLEAR;
}

STUDENT_STATE_t IsQueueEmpty(Queue_t *Pq)
{
    if (Pq)
    {
        if (Pq->front == NULL)
        {
            return STUDENT_STATE_EMPTY;
        }
    }
    return STUDENT_STATE_ERROR;
}

int IsQueueFull(Queue_t *Pq)
{
    return 0;
}

STUDENT_STATE_t checkRoll(Queue_t *Pq, int roll)
{
    QueueNode_t *Qn = (QueueNode_t *)malloc(sizeof(QueueNode_t));
    if (IsQueueEmpty(Pq) == STUDENT_STATE_EMPTY || !Pq || !Qn)
    {
        return STUDENT_STATE_ERROR;
    }
    int i = 0;
    Qn = Pq->front;
    while (Qn)
    {
        if (roll == Qn->student.roll)
        {
            return STUDENT_STATE_FIND;
        }
        Qn = Qn->next;
    }
    return STUDENT_STATE_ERROR;
}