/*****************************************************\
|          BINARY TREE TRAVERSALS SIMULATION          |
|              -> Preorder                            |
|              -> Inorder                             |
|              -> Postorder                           |
|                                                     |
|          By: SEBA Sonia Bouchra                     |
\*****************************************************/

/**You can modify the tree using create_btree function (do not exceed height over 5 ) but it is advisable to keep the current
tree, as changing it may cause overlaps*/

#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"

//colors
const COLORS color1=MAGENTA; //main text
const COLORS color2=YELLOW;  //main background
const COLORS color3=WHITE;   //highlighted text
const COLORS color4=GREEN;   //highlight
const COLORS color5=CYAN;    //title highlight, tree traversed nodes
const COLORS color6=RED;     //tree current node

const int spacing=20;     //initial space between nodes

//declare structure
typedef struct node{
    int info;
    struct node* fg;
    struct node* fd;
}node;

//create node in tree
node* create_node(int val){
    node* root=malloc(sizeof(node));

    if (root==NULL){
        printf("allocation error");
        exit(1);
    }
    root->info=val;
    root->fd=NULL;
    root->fg=NULL;

    return root;
}

//check if tree is empty
int empty_tree(node* root){
    return (root == NULL);
}

//insertion of one node
void insert(node **root,int val){
    if (empty_tree(*root)){
        *root=create_node(val);
        return;
    }else{
        if ((*root)->info<val){
            insert(&((*root)->fd),val);
        }else{
            insert(&((*root)->fg),val);
        }
    }
}

//insert every number in a binary tree
void create_btree(node **root){
    insert(&(*root),55);
    insert(&(*root),22);
    insert(&(*root),15);
    insert(&(*root),30);
    insert(&(*root),37);
    insert(&(*root),10);
    insert(&(*root),9);
    insert(&(*root),67);
    insert(&(*root),80);
    insert(&(*root),100);
    insert(&(*root),19);
    insert(&(*root),85);
    insert(&(*root),70);
}

//function to draw a filled frame
void draw_filled_frame(int x1, int y1, int x2, int y2, int color) {
    textbackground(color);
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            gotoxy(x, y);
            putch(' '); // Fill the area with spaces of the specified background color
        }
    }
}

// Function to draw a rectangle
void drawRectangle(int left, int top, int width, int height) {
    int right = left + width - 1;
    int bottom = top + height - 1;

    // Draw the top edge
    gotoxy(left, top);
    for (int i = 0; i < width; i++) {
        putchxy(left + i, top, '*');
    }
    // Draw the bottom edge
    gotoxy(left, bottom);
    for (int i = 0; i < width; i++) {
        putchxy(left + i, bottom, '*');
    }
    // Draw the left and right edges
    for (int i = 1; i < height - 1; i++) {
        putchxy(left, top + i, '*');
        putchxy(right, top + i, '*');
    }
}

//draw the binary tree
void preorder_draw(node* root,int x, int y,int n){  //x,y:coordinates n:spacing decrease as the tree go longer
    int i;

    if (root != NULL){
        textcolor(color3);textbackground(color4);
        gotoxy(x-1,y);
        printf("     ");
        gotoxy(x,y);
        printf("%03d", root->info);
        textbackground(color2);textcolor(color1);
        //draw left branch
        if (root->fg != NULL){
            //horizontal branch
            gotoxy(x-spacing+n+2,y);
            for(i=0;i<(spacing-n-3);i++){
                printf("_");
            }
            //vertical branch
            gotoxy(x-spacing+n+1,y+1);printf("|");
            gotoxy(x-spacing+n+1,y+2);printf("|");
        }
        //draw right branch
        if (root->fd != NULL){
            //horizontal branch
            gotoxy(x+4,y);
            for(i=0;i<(spacing-n-3);i++){
                printf("_");
            }
            //vertical branch
            gotoxy(x+spacing-n+1,y+1);printf("|");
            gotoxy(x+spacing-n+1,y+2);printf("|");
        }
        //go to children
        preorder_draw(root->fg,x-spacing+n,y+3,n+5);
        preorder_draw(root->fd,x+spacing-n,y+3,n+5);
    }
}

//Function for simulating pre-order traversal
void simulate_pre(node *root,int x,int y,int n){
    if (root!=NULL){
        textbackground(color6);textcolor(color3);//current node
        gotoxy(x,y);
        printf("%03d", root->info);
        delay(2000);

        textbackground(color5);                  //traversed node
        gotoxy(x,y);
        printf("%03d", root->info);

        simulate_pre(root->fg,x-spacing+n,y+3,n+5);//go to left child

        simulate_pre(root->fd,x+spacing-n,y+3,n+5);//go to right child
    }
}

//Function for simulating in-order traversal
void simulate_in(node *root,int x,int y,int n){
    if (root!=NULL){
        simulate_in(root->fg,x-spacing+n,y+3,n+5);//go to left child

        textbackground(color6);textcolor(color3);//current node
        gotoxy(x,y);
        printf("%03d", root->info);
        delay(2000);

        textbackground(color5);                  //traversed node
        gotoxy(x,y);
        printf("%03d", root->info);

        simulate_in(root->fd,x+spacing-n,y+3,n+5);//go to right child
    }
}

//Function for simulating post-order traversal
void simulate_post(node *root,int x,int y,int n){
    if (root!=NULL){
        simulate_post(root->fg,x-spacing+n,y+3,n+5);//go to left child

        simulate_post(root->fd,x+spacing-n,y+3,n+5);//go to right child

        textbackground(color6);textcolor(color3);//current node
        gotoxy(x,y);
        printf("%03d", root->info);
        delay(2000);

        textbackground(color5);                  //traversed node
        gotoxy(x,y);
        printf("%03d", root->info);
    }
}

//select the traversal
char select_(){
    char ch;
    textbackground(YELLOW);textcolor(MAGENTA);
    gotoxy(45,8);printf("________________________________");
    gotoxy(50,10);printf("Choose the traversal :");
    gotoxy(55,12);printf("1- Preorder");
    gotoxy(55,14);printf("2- Inorder");
    gotoxy(55,16);printf("3- Postrder");
    gotoxy(45,18);printf("________________________________");
    textbackground(color1);textcolor(color3);
    do{
        ch=getch();
    }while(ch!='1' && ch!='2' && ch!='3');
    textbackground(color5);textcolor(color3);
    switch(ch){
            case '1':
                gotoxy(54,12);printf("             ");
                gotoxy(55,12);printf("1- Preorder");
                break;
            case '2':
                gotoxy(54,14);printf("            ");
                gotoxy(55,14);printf("2- Inorder");
                break;
            case '3':
                gotoxy(54,16);printf("             ");
                gotoxy(55,16);printf("3- Postrder");
                break;
        }
    return ch;
}

int main()
{
    int n=0;            //initial spacing decrease as the tree go longer
    int x=60;           //vertical coordinate
    int y=5;            //horizontal coordinate

    node *root=NULL; //tree root
    char traversal;  //traversal choice
    char skip;       //skip simulation
    int i;           //coordinates
    int j;

    //first page
    textbackground(color2);clrscr();
    textcolor(color3);
    draw_filled_frame(41,12,80,16,color5);//left, top, right, bottom, color
    drawRectangle(41, 12, 40, 5);//left, top, width, height
    gotoxy(45,14);
    printf("BINARY TREE TRAVERSALS SIMULATION");
    getch();clrscr();

    //creation of the tree
    textbackground(color2);clrscr();
    create_btree(&root);
    textbackground(color4);
    printf("Binary tree created successfully!\n\n");
    textbackground(color2);textcolor(color1);
    printf("\n\nPress the Enter key to continue...");
    getch();clrscr();

    //select the traversal
    traversal = select_();
    textbackground(color2);textcolor(color1);
    gotoxy(1,22);printf("Press the Enter key to continue...");
    getch();clrscr();

    //draw tree
    textbackground(color2);clrscr();
    preorder_draw(root,x,y,n);

    //simulation
    printf("\n\n\n\n\nPress the Enter key to start simulation, press 'e' to exit");
    i=wherex();
    j=wherey();
    skip=getch();
    delline();
    if (skip != 'e'){
        switch(traversal){
            case '1':
                simulate_pre(root,x,y,n);
                break;
            case '2':
                simulate_in(root,x,y,n);
                break;
            case '3':
                simulate_post(root,x,y,n);
                break;
        }
        textbackground(color4);textcolor(color3);
        gotoxy(i,j);
        printf("\n\nSimulation ended successfully successfully!");
        getch();clrscr();
    }

    //end of program
    textcolor(color1);textbackground(color2);
    clrscr();

    return 0;
}


