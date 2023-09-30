#include "Student.h"
void Display(QUEUEENTRY *);
Queue_t gFirstStudent = {0};
int main(void)
{   
    initializeQueue(&gFirstStudent);
    int order = 0;
    PRINT("Welcome to the Student Managment Systems\n");
    while (1)
    {
        PRINT("Choose the task that you want to perform\n");
        PRINT("1. Add the student details manually\n");
        PRINT("2. Add the student details from a text file\n");
        PRINT("3. Find the student details by roll number\n");
        PRINT("4. Find the student details by first name\n");
        PRINT("5. Find the student details by course ID\n");
        PRINT("6. Find the total number of students\n");
        PRINT("7. Delete the student details by roll number\n");
        PRINT("8. Update the student details by roll number\n");
        PRINT("9. Show all information\n");
        PRINT("10. Delete All Students\n");
        PRINT("11. To Exit\n");
        PRINT("Enter your choice to perform the task: ");
        scanf("%d", &order);
        fflush(stdin);
        PRINT("-----------------------------------------\n");
        switch (order)
        {
        case 1:
            if(addStudentManually(&gFirstStudent) == STUDENT_STATE_ADD){}
            break;
        case 2:
            if(addStudentFromFile(&gFirstStudent) == STUDENT_STATE_ADD){}
            break;
        case 3:
            if(findStudentRoll(&gFirstStudent, Display) == STUDENT_STATE_FIND){}
            break;
        case 4:
            if(findStudentFname(&gFirstStudent, Display) == STUDENT_STATE_FIND){}
            break;
        case 5:
            if(findStudentCouseId(&gFirstStudent, Display) == STUDENT_STATE_FIND){}
            break;
        case 6:
            if(countStudent(&gFirstStudent) == STUDENT_STATE_COUNT){}
            break;
        case 7:
            if(deleteStudentRoll(&gFirstStudent) == STUDENT_STATE_DELETE){}
            break;
        case 8:
            if(updateStudent(&gFirstStudent) == STUDENT_STATE_UPDATE){}
            break;
        case 9:
            if(showStudent(&gFirstStudent, Display) == STUDENT_STATE_DISPLAY){}
            break;
        case 10:
            if(deleteAllStudents(&gFirstStudent) == STUDENT_STATE_CLEAR){}
            break;
        case 11:
            exit(1);
            break;
        default:
            break;
        }
    }
    return 0;
}

/**
 * @brief  Displaying elements.
 *
 *  This function is used to print an element of the list
 *  using the PRINT() function.

 * @param PStudent: It is a pointer to struct student data
 *
 * @return It returns nothing
 */
void Display(QUEUEENTRY *PStudent)
{
    PRINT("\nThe student details are");
    PRINT("\n\tThe student roll number is :%d ", PStudent->roll);
    PRINT("\n\tThe student first name is :%s ", PStudent->fname);
    PRINT("\n\tThe student last name is :%s ", PStudent->lname);
    PRINT("\n\tThe student GPA is :%.1f ", PStudent->GPA);
    int i = 0;
    for (i = 0; i < 5; i++)
    {
        PRINT("\n\tThe course ID is: %d", PStudent->cid[i]);
    }
    PRINT("\n-----------------------------------------\n");
}