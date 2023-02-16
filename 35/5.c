#include <stdio.h>
#include <stdlib.h>

#include "student_funcs.c"

#define START_COUNT 3


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("There are too many arguments!\n");
        return 1;
    }

    if (argc < 2)
    {
        printf("You should pass the path to file!\n");
        return 2;
    }


    int count_notes = START_COUNT, line_corrupt = 0;

    Student *studs = (Student *) malloc(sizeof(Student) * count_notes);
    if (NULL == studs)
    {
        printf("Cannot allocate memory!\n");
        return 3;
    }

    FILE *f = fopen(argv[1], "r");
    if (NULL == f)
    {
        printf("Such file does not exists!\n");
        free_students(studs, count_notes);
        return 4;
    }


    int err = read_file(f, &studs, &count_notes, &line_corrupt);
    fclose(f);
    if (err == 1)
    {
        printf("There is not enough memory!\n");
        return -1;
    }
    else if (err >= 4)
    {
        printf("File is corrupted!\nWrong ");
        switch (err)
        {
            case 4:
                printf("ID");
                break;
            case 5:
                printf("Name");
                break;
            case 6:
                printf("Last name");
                break;
            case 7:
                printf("Course");
                break;
            case 8:
                printf("Group");
                break;
            case 9:
                printf("Grade");
                break;
            default:
                printf("Something...");
        }
        printf(" at the line %d\n", line_corrupt);
        free(studs);
        return 5;
    }

    if (count_notes == 0)
    {
        printf("File is empty!\n");
        return 10;
    }

    printf("%s\n", studs->name);


    err = trace(studs, count_notes, argv[1]);
    if (err)
    {
        return 1;
    }

    int count_new = 0;
    Student *new_collection = (Student *) malloc(sizeof(Student) * count_notes);
    if (NULL == new_collection)
    {
        printf("There is not enough memory!\n");
        return 1;
    }



    int cur_len = START_COUNT, action, attempts = 3, i;
    char *num = (char *) malloc(sizeof(char) * cur_len);
    
    while (attempts)
    {
        printf("To find enter 1\nTo sort enter 2\nTo go through enter 3:\n");

        err = get_input(num, &cur_len);
        if (err == 1)
        {
            printf("There is not enough memory!\n");
            free(num);
            return 1;
        }
        

        err = validate(num, &action, 1, 3);
        if (err)
        {
            --attempts;

            if (attempts == 0)
            {
                printf("Too many attempts!\n");
                return 10;
            }
            printf("Try again\n");
        }
        else if (action == 1)
        {
            // find
            attempts = 3;
            while (attempts)
            {
                printf("Find by\n1 - id\n2 - name\n3 - last name\n4 - course\n5 - group\n");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                    break;
                }

                err = validate(num, &action, 1, 5);
                if (err)
                {
                    --attempts;
                    if (attempts == 0)
                    {
                        printf("Too many attempts!\n");
                        return 10;
                    }
                    printf("Try again\n");
                    continue;
                }

                printf("Enter the value:\n");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                    break;
                }

                if (count_new != 0)
                {
                    free_students(new_collection, count_new);
                    new_collection = (Student *) malloc(sizeof(Student) * count_notes);
                    if (NULL == new_collection)
                    {
                        err = 0;
                        break;
                    }
                    count_new = 0;
                }

                err = find_students(studs, new_collection, action, count_notes, &count_new, num);
                if (err == 1)
                {
                    break;
                }

                for (i = 0; i < count_new; ++i)
                {
                    print_student(new_collection + i);
                }
                break;
            }
            if (err == 1)
            {
                printf("There is not enough memory!\n");
                free(num);
                return 1;
            }
            
        }
        else if (action == 2)
        {
            // sort
            attempts = 3;
            while (attempts)
            {
                printf("Sort by\n1 - id\n2 - name\n3 - last name\n4 - group\n");
                err = get_input(num, &cur_len);
                if (err == 1)
                {
                   printf("There is not enough memory!\n");
                    free(num);
                    break;
                }

                err = validate(num, &action, 1, 4);
                if (err)
                {
                    --attempts;
                    if (attempts == 0)
                    {
                        printf("Too many attempts!\n");
                        return 10;
                    }
                    printf("Try again\n");
                    continue;
                }

                if (count_new != 0)
                {
                    switch (action)
                    {
                        case 1:
                            qsort(new_collection, count_new, sizeof(Student), cmp_id);
                            break;
                        case 2:
                            qsort(new_collection, count_new, sizeof(Student), cmp_name);
                            break;
                        case 3:
                            qsort(new_collection, count_new, sizeof(Student), cmp_last_name);
                            break;
                        case 4:
                            qsort(new_collection, count_new, sizeof(Student), cmp_group);
                            break;
                    }
                    for (i = 0; i < count_new; ++i)
                    {
                        print_student(new_collection + i);
                    }
                }
                else
                {
                    switch (action)
                    {
                        case 1:
                            qsort(studs, count_notes, sizeof(Student), cmp_id);
                            break;
                        case 2:
                            qsort(studs, count_notes, sizeof(Student), cmp_name);
                            break;
                        case 3:
                            qsort(studs, count_notes, sizeof(Student), cmp_last_name);
                            break;
                        case 4:
                            qsort(studs, count_notes, sizeof(Student), cmp_group);
                            break;
                    }
                    for (i = 0; i < count_notes; ++i)
                    {
                        print_student(studs + i);
                    }
                }
                break;
            }
        }
        else
        {
            break;
        }
    }
    free(num);

    if (attempts == 0)
    {
        printf("Too many attempts!\n");
        return 10;
    }


    printf("Students and their average grades:\n");
    for (i = 0; i < count_notes; ++i)
    {
        student_out(studs + i);
    }

    
    Student_list *student_lists = by_course(studs, count_notes);

    Node *st;

    for (i = 0; i < 4; ++i)
    {
        st = (student_lists + i)->first;
        printf("\nCourse %d:\n\n", i + 1);
        while (st != NULL)
        {
            print_student(st->student);
            st = st->next;
        }
    }
    

    for (i = 0; i < 4; ++i)
    {
        clear_list(student_lists + i);
    }
    free(student_lists);


    for (i = 0; i < count_new; ++i)
    {
        print_student(new_collection + i);
    }

    free_students(studs, count_notes);
    free_students(new_collection, count_new);


    return 0;
}