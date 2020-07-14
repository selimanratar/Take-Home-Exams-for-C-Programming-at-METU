#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/



void initialize_the_tree(int binary_tree[MAX_LENGTH], int get_values_from_user) {
    /* Silence is golden */
    long i,loop_num,index_num,node_val,iter_1;
    long indexes[MAX_LENGTH];
    int checker;
    
    /* add -1's everywhere */
    for (i = 0; i < MAX_LENGTH; i++){
            binary_tree[i] = -1;
        }
    
        
    if (get_values_from_user){
        scanf("%ld",&loop_num);
        for (i = 0; i < loop_num; i++){
            scanf("%ld %ld",&index_num,&node_val);
            checker = 0;
            
            /*checkin' whether the node is proper or nah */
            for (iter_1 = 0; iter_1 < loop_num; iter_1++){
                if (index_num == indexes[iter_1]*2+2 || index_num == indexes[iter_1]*2+1 || index_num == 0){
                    checker = 1;
                }
                    
            }
            
            /* the final deal */
            if(binary_tree[index_num] == -1 && checker){
                binary_tree[index_num] = node_val;
                indexes[i] = index_num;
            }
            
        }
         
        
    }
        
    
}


/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int node, char where, int value) {
    /* Silence is golden */
    long iter_1, iter_2;
    long indexes[MAX_LENGTH];
    int checker;
    
    /* storing indexes here */
    for (iter_2 = 0; iter_2 < MAX_LENGTH; iter_2++){
        if (binary_tree[iter_2] != -1){
            indexes[iter_2] = iter_2;
        }
    }
    

    for (iter_1 = 0; iter_1 < MAX_LENGTH; iter_1++){
        if (node == indexes[iter_1]*2+2 || node == indexes[iter_1]*2+1 || node == 0){
            checker = 1;
        }
                    
    }
    
    if (where == 'l' && checker){
        if (binary_tree[2*node+1] == -1){
            binary_tree[2*node+1] = value;
        }
    }
    if (where == 'r' && checker){
        if (binary_tree[2*node+2] == -1){
            binary_tree[2*node+2] = value;
        }
    }
    if (where == 'i' && checker){
        if (binary_tree[node] == -1){
            binary_tree[node] = value;
        }
    }
}


/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    /* Silence is golden */
    /* regular case with given node existing */
    if (binary_tree[node] != -1){
        binary_tree[node] = -1;
        
        /*case for ONLY RIGHT child */
        if (binary_tree[2*node+1] == -1 && binary_tree[2*node+2] != -1 && 2*node+2 < MAX_LENGTH){
            delete_node_rec(binary_tree, 2*node+2);
        }
        
       /*case for ONLY LEFT child */
        if (binary_tree[2*node+1] != -1 && binary_tree[2*node+2] == -1 && 2*node+1 < MAX_LENGTH){
            delete_node_rec(binary_tree, 2*node+1);
        }
        
        /*case for BOTH */
        if (binary_tree[2*node+1] != -1 && binary_tree[2*node+2] != -1 && 2*node+1 < MAX_LENGTH){
            delete_node_rec(binary_tree, 2*node+2);
            delete_node_rec(binary_tree,2*node+1);
        }
    }
}


/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
 
void put_tab(int reps){
    if (reps > 0){
        printf("\t");
        put_tab(reps-1);
    }
}

void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    /* Silence is golden */
    int rep_num = depth;
    
    if (binary_tree[root] != -1 && depth >= 0){
        
        if (2*root+1 < MAX_LENGTH){
        draw_binary_tree_rec(binary_tree, 2*root+1, depth-1);
        }
        
        put_tab(rep_num);
        printf("%d\n",binary_tree[root]);
        
        if (2*root+2 < MAX_LENGTH){
        draw_binary_tree_rec(binary_tree, 2*root+2, depth-1);
        }
    }
    
    else if (binary_tree[root] != -1 && depth >-1 && 2*root+1 < MAX_LENGTH && 2*root+2 == MAX_LENGTH){
        printf("%d\n",binary_tree[2*root+1]);
        printf("\t%d\n",binary_tree[root]);
    }

}


/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */

int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int from_left = 0;
    int from_right = 0;
    
    if (binary_tree[root] != -1 && 2*root+2 < MAX_LENGTH){
        
        /* is a LEAF */
        if (binary_tree[2*root+1] == -1 && binary_tree[2*root+2] == -1){
            return 0;
        }
        
        /* has ONLY LEFT */
        else if (binary_tree[2*root+1] != -1 && binary_tree[2*root+2] == -1){
            return 1+find_height_of_tree_rec(binary_tree,2*root+1);
        }
        
        /* has ONLY RIGHT */
        else if (binary_tree[2*root+1] == -1 && binary_tree[2*root+2] != -1){
            return 1+find_height_of_tree_rec(binary_tree,2*root+2);
        }
        
        /* has BOTH */
        else if (binary_tree[2*root+1] != -1 && binary_tree[2*root+2] != -1){
            from_left = 1+find_height_of_tree_rec(binary_tree,2*root+1);
            from_right = 1+find_height_of_tree_rec(binary_tree,2*root+2);
            
            if (from_left >= from_right){
                return from_left;
            }
            
            else{
                return from_right;
            }
        }
    }
    
    return 0;
}


/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
 
/*int minimum_helper(int binary_tree[MAX_LENGTH], int to_compare, int minim){
    int left_side;
    if (binary_tree[to_compare] != -1){
        
        if (binary_tree[to_compare] <= minim){
            minim = binary_tree[to_compare];
        }
        
        left_side = minimum_helper(binary_tree, to_compare*2+1, minim); 
        
        if (left_side <= minim){
            minim = left_side;
        } 
        return (minimum_helper(binary_tree, 2*to_compare+2, minim));
    }
    
    return minim;
}

int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int minim = binary_tree[root];
    if (minim != -1){
        return minimum_helper(binary_tree, root, minim);
    }
    return MIN_VAL;
}*/
void initialize_family(int another_array[MAX_LENGTH], int call_num){
    
    if (call_num < MAX_LENGTH){
        another_array[call_num] = MAX_VAL;
        initialize_family(another_array, call_num+1);
    }
    
}


void family(int binary_tree[MAX_LENGTH],int another_array[MAX_LENGTH],int root, int index_num){
            
  	if(root < MAX_LENGTH && binary_tree[root] != -1){
        another_array[root] = binary_tree[root];
    }
    
 	/* case for BOTH */
 	if(2*root+2 < MAX_LENGTH && binary_tree[2*root+1] != -1 && binary_tree[2*root+2] != -1){
 	    family(binary_tree, another_array, 2*root+1, index_num+1);
 	    family(binary_tree, another_array, 2*root+2, index_num+1);
 	}
 	
 	/* case for ONLY LEFT */
 	if(2*root+2 < MAX_LENGTH && binary_tree[2*root+1] != -1 && binary_tree[2*root+2] == -1){
 	    family(binary_tree, another_array, 2*root+1, index_num+1);
 	}
 	
 	/* case for ONLY RIGHT */
 	if(2*root+2 < MAX_LENGTH && binary_tree[2*root+1] == -1 && binary_tree[2*root+2] != -1){
 	    family(binary_tree, another_array, 2*root+2, index_num+1);
 	}

 }


int minimum_now(int another_array[MAX_LENGTH], int minim, int call_num){
    
    if (another_array[call_num] == MAX_VAL && call_num < MAX_LENGTH){
        return minimum_now(another_array, minim, call_num+1);
    }
    
    if (call_num < MAX_LENGTH){
        if (another_array[call_num] <= minim){
            minim = another_array[call_num];
            return minimum_now(another_array, minim, call_num+1);
        }
        
        return minimum_now(another_array, minim, call_num+1);
        
    }
    
    return minim;
}


int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root){    
    int another_array[MAX_LENGTH];
    int minim = MAX_VAL;

    if (root < MAX_LENGTH && binary_tree[root] != -1 && 2*root+1 < MAX_LENGTH){
        initialize_family(another_array, 0);
        family(binary_tree, another_array, root, 0);
        return minimum_now(another_array, minim, 0);
    }
    
    return MIN_VAL;
}


/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
 
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    int travel_1, travel_2, i;
    int our_new_array[MAX_LENGTH];
    if (binary_tree[root] == -1){
        return -1;
    }
    
    else if (binary_tree[root] != value && binary_tree[2*root+1] == -1 && binary_tree[2*root+2] == -1){
        return -1;
    }
    
    
    for (i = 0; i < MAX_LENGTH; i++){
            our_new_array[i] = -1;
        }
        
    our_new_array[0] = root;
    
    if (binary_tree[root] == value){
        return root;
    }

    for (travel_1 = root; travel_1 < MAX_LENGTH; travel_1++){
        
        if (binary_tree[travel_1]!= -1){
            
            for (travel_2 = 0; travel_2 < MAX_LENGTH; travel_2++){
                
                if (travel_1 == 2*our_new_array[travel_2]+1){
                    if (binary_tree[travel_1] == value){
                        
                        return travel_1;
                    }
                    our_new_array[2*travel_2+1] = travel_1;
                    break;
                }
                
                else if (travel_1 == 2*our_new_array[travel_2]+2){
                    if (binary_tree[travel_1] == value){
                        return travel_1;
                    }
                    our_new_array[2*travel_2+2] = travel_1;
                    break;

                }
            }
        }
    }
    return -1;
}

/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    int from_left = -1;
    int from_right = -1;
    if (root > MAX_LENGTH-1){
        return -1;
    }
    
    /* all the way to left */
    if (binary_tree[root] != -1 && value != -1 && root < MAX_LENGTH && 2*root+1 < MAX_LENGTH){
        from_left = depth_first_search_rec(binary_tree, 2*root+1, value);
    }
        
    if (from_left != -1){
        return from_left;
    }
    
    /* starting to check whether the values trying hold or nah */
    if (binary_tree[root] == value){
        return root;
    }
    
    /* all the way to right */
    if (binary_tree[root] != -1 && value != -1 && root < MAX_LENGTH && 2*root+2 < MAX_LENGTH){
        from_right = depth_first_search_rec(binary_tree, 2*root+2, value);
    }
    
    if (from_right != -1){
        return from_right;
    }
    return -1;
}


/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }

}



