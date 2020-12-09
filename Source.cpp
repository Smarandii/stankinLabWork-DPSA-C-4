#include <cstdio>
#include <cstdlib>
#include <clocale>

bool ACCESS_IS_GRANTED = false;
bool* ACCESS_IS_GRANTED_POINTER = &ACCESS_IS_GRANTED;

struct List
{
    List* next_el;
    char symbol;
};

void grant_access(bool*);
void print_list(List*);
int calculate_lenght(List*);
void process_string(List*);
void check_error(List*);

void grant_access(bool* flag) {
    if (!*flag) *flag = true;
    printf("[!]ACCESS GRANTED[!]");
}
void close_access(bool* flag) {
    if (*flag) *flag = false;
    printf("[!]ACCESS CLOSED[!]");
}
bool check_access(bool* flag, int menu = 0) {
    if (*flag && menu == 14) { printf("[!]CLOSE ACCESS BEFORE EXIT[!]"); return true; }
    if (!*flag && menu == 14) { return false; }
    if (!(*flag)) { printf("[!]ACCESS NOT GRANTED, USE OPERATION 'GRANT ACCESS' TO START[!]"); return false; }
    if (*flag) return true;
}
void check_error(List* pointer) {
    if (pointer == NULL)
    {
        printf("[!]MEMORY ALLOCATION ERROR[!]\n");
        exit(0);
    }
}

void empty_list(List*& begin_pointer, List*& work_pointer) {
    List* wp;
    if (check_access(ACCESS_IS_GRANTED_POINTER)) {
        wp = begin_pointer;
        while (wp != NULL)
        {

            wp = begin_pointer->next_el;
            free(begin_pointer);
            begin_pointer = wp;
        }
        begin_pointer = NULL;
        work_pointer = NULL;
    }
}
bool check_empty_list(List* begin_pointer) {
    if (begin_pointer == NULL) { printf("[!]LIST IS EMPTY[!]"); return true; }
    else { printf("[!]LIST IS NOT EMPTY[!]"); return false; }
}

List* set_work_pointer_to_begin(List* begin_pointer, List* work_pointer) {
    work_pointer = begin_pointer;
    return work_pointer;
}
bool check_work_pointer_on_end(List* work_pointer) {
    if (work_pointer->next_el == NULL) { printf("[!]WORK POINTER IS AT THE END OF LIST[!]"); return true; }
    else { printf("[!]WORK POINTER IS NOT AT THE END OF LIST[!]"); return false; }
}
int move_work_pointer_right(List*& begin_pointer, List*& work_pointer, int position) {
    if (!check_work_pointer_on_end(work_pointer)){
        work_pointer = work_pointer->next_el;
        position = position + 1;
    }
    return position;
}


List* delete_element_next_to_work_pointer(List* begin_pointer, List* work_pointer) {
    if (!check_work_pointer_on_end(work_pointer)){
        List* next_to_work_pointer = work_pointer->next_el;
        work_pointer->next_el = next_to_work_pointer->next_el;
        free(next_to_work_pointer);
        return work_pointer;
    }

}

int cut_element_next_to_work_pointer(List*& begin_pointer, List*& work_pointer) {
    if (!check_work_pointer_on_end(work_pointer))
    {
        List* next_to_work_pointer = work_pointer->next_el;
        int element = next_to_work_pointer->symbol;
        printf("\nELEMENT: %c", element);
        work_pointer->next_el = next_to_work_pointer->next_el;
        free(next_to_work_pointer);
        return element;
    }
}

List* edit_element_next_to_work_pointer(List* begin_pointer, List* work_pointer) {
    if (!check_work_pointer_on_end(work_pointer))
    {
        List* next_to_work_pointer = work_pointer->next_el;
        printf("\nPRINT NEW ELEMENT: ");
        scanf("%s", &next_to_work_pointer->symbol);
        return work_pointer;
    }
}

void add_element_next_to_work_pointer(List*& begin_pointer, List*& work_pointer) {
    List* new_element = (List*)malloc(sizeof(List));
    check_error(new_element);
    if (begin_pointer != NULL)
    {
        List* next_to_work_pointer = work_pointer->next_el;
        new_element->next_el = next_to_work_pointer; 
        work_pointer->next_el = new_element;
        printf("PRINT NEW ELEMENT: ");
        scanf("%s", &new_element->symbol);
    }
    else {
        
        printf("PRINT NEW ELEMENT: ");
        scanf("%s", &new_element->symbol);
        begin_pointer = new_element;
        begin_pointer->next_el = NULL;
        work_pointer = begin_pointer;
    }

}


void print_list(List* begin_pointer, List* work_pointer, int pos)
{
    check_error(begin_pointer);
    printf("\nLIST: ");
    while (begin_pointer != NULL) {
        printf("%c", begin_pointer->symbol);
        begin_pointer = begin_pointer->next_el;
    }
    
    printf("\nWORK POINTER: %d", pos);
}
void print_element_next_to_work_pointer(List* work_pointer)
{
    printf("ELEMENT: %c\n", work_pointer->next_el->symbol);
}


int calculate_lenght(List* begin_pointer)
{
    int i = 1;
    for (i; begin_pointer->next_el != NULL; i++) begin_pointer = begin_pointer->next_el;
    return i;
}
void process_string(List* begin_pointer)
{
    int counter = 0;
    bool contains_five_e = false;
    List* cursor = begin_pointer;
    while (cursor->next_el != NULL)
    {
        if (cursor->symbol == 'e' || cursor->symbol == 'E') counter++;
        else
            if (counter >= 5)
            {
                contains_five_e = true;
                break;
            }
            else(counter = 0);
        cursor = cursor->next_el;
    }
    if (contains_five_e) printf("this string contains 5 or more e");
    else printf("this string contains less than 5 e");
}




void main()
{
    int menu;
    int pos = 1;
    List* begin_pointer = NULL; 
    List* work_pointer = NULL;
    int buffer = (int)malloc(sizeof(int));
    while (true) {
        printf("\n----------------\n \
Menu:\n\n \
1)Grant access\n \
2)Empty list\n \
3)Check if list is empty\n \
4)Set work pointer on begin of list\n \
5)Check if work pointer on end of list\n \
6)Move work pointer to next element\n \
7)Print element next from work pointer\n \
8)Delete element next from work pointer\n \
9)Cut element next from work pointer\n \
10)Edit element next from work pointer\n \
11)Add element next from work pointer\n \
12)Print\n \
13)Close access\n \
14)Exit\n \
\n----------------\n");
        scanf("%d", &menu);

        if (menu == 1) { grant_access(ACCESS_IS_GRANTED_POINTER); continue; }

        if (menu == 14 && !check_access(ACCESS_IS_GRANTED_POINTER, menu)) { exit(0); }

        else 
        {
            if (check_access(ACCESS_IS_GRANTED_POINTER)) {

                if (menu == 2) { empty_list(begin_pointer, work_pointer); continue; }

                if (menu == 3) { check_empty_list(begin_pointer); continue; }

                if (!check_empty_list(begin_pointer))
                {
                
                    if (menu == 4) { work_pointer = set_work_pointer_to_begin(begin_pointer, work_pointer); pos = 1; continue; }

                    if (menu == 5) { check_work_pointer_on_end(work_pointer); continue; }

                    if (menu == 6) { pos = move_work_pointer_right(begin_pointer, work_pointer, pos); continue; }

                    if (menu == 7) { print_element_next_to_work_pointer(work_pointer); continue;  }

                    if (menu == 8) { delete_element_next_to_work_pointer(begin_pointer, work_pointer); continue;  }

                    if (menu == 9) { buffer = cut_element_next_to_work_pointer(begin_pointer, work_pointer); continue; }

                    if (menu == 10) { edit_element_next_to_work_pointer(begin_pointer, work_pointer); continue; }

                    if (menu == 12) { print_list(begin_pointer, work_pointer, pos); continue; }
                }

                if (menu == 11) { add_element_next_to_work_pointer(begin_pointer, work_pointer); continue; }

                if (menu == 13) close_access(ACCESS_IS_GRANTED_POINTER);
        
            }
        }
    }
}