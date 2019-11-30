#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FindGraphLoops(int num, char name[num][100], int graph_table[num][num]){
    for(int i=0; i<num; i++){
        printf("For el. '%s' there is/are %d loops.\n", name[i], graph_table[i][i]);
    }
}

int main(){
    int graph;
        
    printf("1 - graph | 2 - digraph: ");
    scanf("%d", &graph);
    
    if(!( graph == 1 || graph == 2 ))
        exit(11);
    
    printf("num of elements: ");
    int num;
    scanf("%d",&num);
    getchar(); // to ignore \n
    if (num <= 0)
        exit(12);
    
    char name[num][100];
    int graph_table[num][num];
    
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            graph_table[i][j] = 0;
        }
    }
    
    printf("Enter names (less than 100 symb)\n");
    for(int i=0; i<num; i++){
        printf("%d: ",i+1);
        scanf("%s", name[i]);
        for (int j=0; j<i; j++){
            if( strcmp(name[i], name[j]) == 0 ){
                printf("This name allready exist, enter another\n");
                i--;
            }
        }

    }
    getchar(); //from scanf to ignor \n
    
    printf("--------------------------------------------------------------\n");
    printf("Enter for all elements connection according to their position:\n");
    printf("Example:      'first': 7;5;3;4;9;6;1;8;       (to end - enter)\n");
    printf("--------------------------------------------------------------\n");
    for(int i=0; i<num; i++){
        printf("'%s': ",name[i]);
        char c;
        int temp_num = 0;
        while( (c=getchar()) != '\n' ){
            if(c == ';'){
                if(temp_num <= num)
                    graph_table[i][temp_num-1]++;
                
                temp_num=0;
            } else if('0' <= c && c <= '9'){
                temp_num *= 10;
                temp_num += c - '0';
            }
        }
    }
    
    printf("\nPrinting Table (press enter)\n");
    getchar(); // wait
    
    int graph_check = 1;
    for(int i=0; i<num; i++){
        int temp_graph_check = 0;
        for(int j=0; j<num; j++){
            if(graph_table[i][j] == 1)
                temp_graph_check = 1;
    
            if(graph_table[j][i] == 1)
                temp_graph_check = 1;
        }
        if(temp_graph_check == 0)
            graph_check=0;
    }
    if(graph_check == 0){
        printf("unrelated graph\n");
    } else {
        printf("related graph\n");

    }
    printf("--------------------\n");

    for(int i=0; i<num; i++) {
        printf("%s | ", name[i]);
        for (int j=0; j<num; j++) {
            printf("%d  ", graph_table[i][j]);
        }
        printf("\n");
    }
    
    FindGraphLoops(num, name, graph_table);
    
    printf("To open and configure file press enter");
    getchar();
    
    char terminal[1000];
    char arrow[3] = "";
    strcat(terminal, "echo '");
    if(graph == 2){
        strcat(terminal, "digraph G {");
        strcat(arrow, "->");
    } else {
        strcat(terminal, "graph G {");
        strcat(arrow, "--");
    }
    for(int i=0; i<num; i++){
        strcat(terminal, name[i]);
        strcat(terminal, "; ");
    }
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            for(int k=0; k<graph_table[i][j]; k++){
                strcat(terminal, name[i]);
                strcat(terminal, arrow);
                strcat(terminal, name[j]);
                strcat(terminal, "; ");
            }
        }
    }
    strcat(terminal, "}' | dot -Tpng > ./graph.png; open ./graph.png");

    system(terminal);
    return 0;
}
