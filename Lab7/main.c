#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;

// tree_t *
// read_a_tree(char *s)
// {
// 	char * begin, * end, * sub ;
// 	int n ;
// 	int data ;	

// 	data = atoi(s) ;
// 	node_t * t = tree_create_node(data) ;

// 	for (begin = s + 1 ; *begin != '(' && *begin != ')' && *begin != ',' ; begin++) ;
// 	if (*begin == ')' || *begin == ',') 
// 		return t ;

// 	// *begin == '('
// 	sub = begin + 1 ;
// 	for (end = begin + 1, n = 0 ; n > 0 || *end != ')' ; end++) {
// 		if (*end == '(') {
// 			n++ ;
// 		}
// 		if (*end == ')') {
// 			n-- ;
// 		}
// 		if (n == 0 && *end == ',') {
// 			tree_add_child(t, read_a_tree(sub)) ;
// 			sub = end + 1 ;
// 		}
// 	}
// 	tree_add_child(t, read_a_tree(sub)) ;

// 	return t ;
// }

int
main ()
{
	// char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;
	// char newline ;
	// //scanf("%255[^\n]", s, &newline) ;

	// tree_t * t ;
	// t = read_a_tree(s) ;
	// tree_print(t) ;

	// printf("height: %d\n", tree_height(t)) ;

	// tree_print(tree_search(t, 3)) ;

    // char a[68];
    // scanf("%s", a);
    // tree_t * t = tree_create_node(a);
    // tree_t * t2 = tree_create_node("b");
    // tree_t *t3 = tree_create_node("cc");
    // tree_t *t4 = tree_create_node("ddd");
    // tree_add_child(t2, t3);
    // tree_add_child(t, t2);
    // tree_add_child(t, t4);
    // tree_print(t);

    char bf1[68];
    char bf2[68];

    tree_t *tree_store[105] = {0x0, };
    char str_store[105][68];
    int is_child[105] = {0, };

    int n, m;
    int cnt = 0;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++)
    {
        scanf("%s", bf1);
        scanf("%s", bf2);
        int j1 = 0, j2 = 0;
        tree_t *t1;
        tree_t *t2;
        for (j1 = 0; j1 < cnt; j1++)
        {
            if (strcmp(str_store[j1], bf1) == 0)
                break;
        }
        if (j1 >= cnt)
        {
            t1 = tree_create_node(bf1);
            strcpy(str_store[j1], bf1);
            tree_store[j1] = t1;
            cnt++;
        }
        else
            t1 = tree_store[j1];
        for (j2 = 0; j2 < cnt; j2++)
        {
            if (strcmp(str_store[j2], bf2) == 0)
                break;
        }
        if (j2 >= cnt)
        {
            t2 = tree_create_node(bf2);
            strcpy(str_store[j2], bf2);
            tree_store[j2] = t2;
            cnt++;
        }
        else
            t2 = tree_store[j2];
        is_child[j2] = 1;
        tree_add_child(t1, t2);
    }

    for (int i = 0; i < n; i++)
    {
        if (!is_child[i])
            tree_print(tree_store[i]);
    }

	return 0 ;
}
