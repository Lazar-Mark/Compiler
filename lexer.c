#include "lexer.h"
#include "error.h"

Vector* tokens;
/*this function receives  one argument that represents the name 
of the file from which all the content is taken and forwards it to the format_data function*/
void load_file(char* name){
    int size=0;
    FILE* file= fopen(name,"r");
    //checking the success of the fopen function
    if(!file)
        LOAD_ERR();
    
    fseek(file,0,SEEK_END);
    size=ftell(file);
    char file_text[size+1];
    rewind(file);
    //takes the content of the file and puts it in the buffer
    fread(file_text,1,size,file);
    fclose(file);
    file_text[size]=0;
    //calls the format_data function
    printf("\nOvo je text %s\n",file_text);
    format_data(file_text);
}
/*Create*/
void create_token(char* word,Token_type type,int line){
    //this function creates dynamically allocated memory for the token structure and assigns values ​​to it
        Token* new_token=(Token*)malloc(sizeof(Token));
        new_token->word=(char*)malloc(sizeof(char)*(strlen(word)+1));
        //checking if memory was successfully allocated
        if(!new_token || !new_token->word) MALLOC_ERR();
                
        strcpy(new_token->word,word);
        new_token->type=type;
        new_token->line=line;

        vector_add(tokens,new_token);        
    
}
void format_data(char* text){
    //converts all text from the buffer into tokens
    int line=0;
    tokens= vector_create();
    char buffer[31+1];
    strcpy(buffer,"");
    while(*text){
        switch(*text){
        case '\n':
            line++;
            text++;
            break;
        case '\"':
            strcpy(buffer,"");
            do{
                strncat(buffer,text,1);
                text++;
                if(*text == '\\' && *(text+1)=='\"'){
                strncat(buffer,text,2);
                text+=2;    
                }
                if(*text == '\"')strncat(buffer,text,1);
                
            }while(*text != '\"');
            printf("\nZavrsio sam i buffer ovako izgleda: %s\n",buffer);
            text++;
            create_token(buffer,STRING_LITERAL,line);
            break;
        case ' ':
            text++;
            break;

        case '\t':
            printf("\nkarakrer je tab\n");
            text++;
            break;
        case '+':
            if(*(text+1)=='+'){
                create_token("++", INCREMENT, line);
                printf("Nasao sam ++\t\n");
                text += 2;
            }
            else if(*(text+1)=='='){
                create_token("+=", ADD_EQ, line);
                printf("Nasao sam +=\t\n");
                text += 2;
            }
            else{
                create_token("+", ADD, line);
                printf("Nasao sam +\t\n");
                text++;
            }
            break;

        case '-':
            if(*(text+1)=='-'){
                create_token("--", DECREMENT, line);
                printf("Nasao sam --\t\n");
                text += 2;
            }
            else if(*(text+1)=='='){
                create_token("-=", SUB_EQ, line);
                printf("Nasao sam -=\t\n");
                text += 2;
            }
            else if(*(text+1)=='>'){
                create_token("->", ARROW, line);
                printf("Nasao sam ->\t\n");
                text += 2;
            }
            else{
                create_token("-", SUB, line);
                printf("Nasao sam -\t\n");
                text++;
            }
            break;

        case '*':
            if(*(text+1)=='='){
                create_token("*=", MUL_EQ, line);
                printf("Nasao sam *=\t\n");
                text += 2;
            }
            else{
                create_token("*", MUL, line);
                printf("Nasao sam *\t\n");
                text++;
            }
            break;

        case '/':
            if(*(text+1)=='/'){
                while(*text!='\n')
                    text++;
            printf("\nNasao sam komentar\n");
            }
            
            else if(*(text+1)=='*'){
                while(*text!='*' && *(text+1)=='/')
                    text++;
            printf("\nNasao sam komentar\n");
            text++;
            }
            else if(*(text+1)=='='){
                create_token("/=", DIV_EQ, line);
                printf("Nasao sam /=\t\n");
                text += 2;
            }
            else{
                create_token("/", DIV, line);
                printf("Nasao sam /\t\n");
                text++;
            }
            break;

        case '=':
            if(*(text+1)=='='){
                create_token("==", EQUAL, line);
                printf("Nasao sam ==\t\n");
                text += 2;
            }
            else{
                create_token("=", ASSIGN, line);
                printf("Nasao sam =\t\n");
                text++;
            }
            break;

        case '%':
            if(*(text+1) == '=') {
                create_token("%%=", MOD_EQ, line);
                printf("Nasao sam %%=\t\n");
                text += 2;
            }
            else {
                create_token("%%", MOD, line);
                printf("Nasao sam %%\t\n"); 
                text++;
            }
            break;

        case '<':
            if(*(text+1)=='<'){;
                create_token("<<", LEFT_SHIFT, line);
                printf("Nasao sam <<\t\n");
                text += 2;
            }
            else if(*(text+1)=='='){
                create_token("<=", LESS_EQ, line);
                printf("Nasao sam <=\t\n");
                text += 2;
            }
            else{
                create_token("<", LESS, line);
                printf("Nasao sam <\t\n");
                text++;
            }
            break;

        case '>':
            if(*(text+1)=='>'){
                create_token(">>", RIGHT_SHIFT, line);
                printf("Nasao sam >>\t\n");
                text += 2;
            }
            else if(*(text+1)=='='){
                create_token(">=", GREATER_EQ, line);
                printf("Nasao sam >=\t\n");
                text += 2;
            }
            else{
                create_token(">", GREATER, line);
                printf("Nasao sam >\t\n");
                text++;
            }
            break;

        case '!':
            if(*(text+1)=='='){
                create_token("!=", NOT_EQUAL, line);
                printf("Nasao sam !=\t\n");
                text += 2;
            }
            else{
                create_token("!", NOT, line);
                printf("Nasao sam !\t\n");
                text++;
            }
            break;

        case '&':
            if(*(text+1)=='&'){
                create_token("&&", AND, line);
                printf("Nasao sam &&\t\n");
                text += 2;
            }
            else if(*(text+1) == '=') {
                create_token("&=", BIT_AND_EQ, line);
                printf("Nasao sam &=\t\n");
                text += 2;
            }
            else{
                create_token("&", BIT_AND, line);
                printf("Nasao sam &\t\n");
                text++;
            }
            break;

        case '|':
            if(*(text+1)=='|'){
                create_token("||", OR, line);
                printf("Nasao sam ||\t\n");
                text += 2;
            }
            else if(*(text+1) == '=') {
                create_token("|=", BIT_OR_EQ, line);
                printf("Nasao sam |=\t\n");
                text += 2;
            }
            else{
                create_token("|", BIT_OR, line);
                printf("Nasao sam |\t\n");
                text++;
            }
            break;

        case '^':
            if(*(text+1) == '=') {
                create_token("&=", BIT_AND_EQ, line);
                printf("Nasao sam &=\t\n");
                text += 2;
            }
            else {
                create_token("^", BIT_XOR, line);
                printf("Nasao sam ^\t\n");
                text++;
                break;
            }

        case '~':
            create_token("~", BIT_NOT, line);
            printf("Nasao sam ~\t\n");
            text++;
            break;

        case '(':
            create_token("(", OPEN_PARENTHESIS, line);
            printf("Nasao sam (\t\n");
            text++;
            break;

        case ')':
            create_token(")", CLOSE_PARENTHESIS, line);
            printf("Nasao sam )\t\n");
            text++;
            break;

        case '{':
            create_token("{", OPEN_BRACE, line);
            printf("Nasao sam {\t\n");
            text++;
            break;

        case '}':
            create_token("}", CLOSE_BRACE, line);
            printf("Nasao sam }\t\n");
            text++;
            break;

        case '[':
            create_token("[", OPEN_BRACKET, line);
            printf("Nasao sam [\t\n");
            text++;
            break;

        case ']':
            create_token("]", CLOSE_BRACKET, line);
            printf("Nasao sam ]\t\n");
            text++;
            break;

        case ';':
            create_token(";", SEMICOLON, line);
            printf("Nasao sam ;\t\n");
            text++;
            break;

        case ',':
            create_token(",", COMMA, line);
            printf("Nasao sam ,\t\n");
            text++;
            break;  
        case '.':
            create_token(".", DOT, line);
            printf("Nasao sam .\t\n");
            text++;
            break;

        default:
            strncat(buffer,text,1);
            //printf("\nTrenutno u bufferu %s a karakter je %c\n",buffer,*text);
            if(strncmp(text,"int",3)==0 && !(*(text+4)=='_' || isalnum(*(text+4)))){
                create_token("int", INT, line);
                strcpy(buffer,"");
                text+=3;
            }
            else if(strncmp(text,"float",5)==0 && !(*(text+6)=='_' || isalnum(*(text+6)))){
                create_token("float",FLOAT,line);
                strcpy(buffer,"");
                text+=5;
            }
            else if(strncmp(text,"double",6)==0 && !(*(text+7)=='_' || isalnum(*(text+7)))){
                create_token("double",DOUBLE,line);
                strcpy(buffer,"");
                text+=6;
            }
            else if(strncmp(text,"char",4)==0 && !(*(text+5)=='_' || isalnum(*(text+5)))){
                create_token("char",CHAR,line);
                strcpy(buffer,"");
                text+=4;
            }
            else if(strncmp(text,"void",4)==0 && !(*(text+5)=='_' || isalnum(*(text+5)))){
                create_token("void",VOID,line);
                strcpy(buffer,"");
                text+=4;
            }
            else if(strncmp(text,"unsigned",8)==0 && !(*(text+9)=='_' || isalnum(*(text+9)))){
                create_token("unsigned",UNSIGNED,line);
                strcpy(buffer,"");
                text+=8;
            }
            else if(strncmp(text,"signed",6)==0 && !(*(text+7)=='_' || isalnum(*(text+7)))){
                create_token("signed",SIGNED,line);
                strcpy(buffer,"");
                text+=6;
            }
            else if(strncmp(text,"short",5)==0 && !(*(text+6)=='_' || isalnum(*(text+6)))){
                create_token("short",SHORT,line);
                strcpy(buffer,"");
                text+=5;
            }
            else if(strncmp(text,"long",4)==0 && !(*(text+5)=='_' || isalnum(*(text+5)))){
                create_token("long",LONG,line);
                strcpy(buffer,"");
                text+=4;
            }
            else if(strncmp(text,"while",5)==0 && !(*(text+6)=='_' || isalnum(*(text+6)))){
                create_token("while",WHILE,line);
                strcpy(buffer,"");
                text+=5;
            }
            else if(strncmp(text,"do",2)==0 && !(*(text+3)=='_' || isalnum(*(text+3)))){
                create_token("do",DO,line);
                strcpy(buffer,"");
                text+=2;
            }
            else if(strncmp(text,"for",3)==0 && !(*(text+4)=='_' || isalnum(*(text+4)))){
                create_token("for",FOR,line);
                strcpy(buffer,"");
                text+=3;
            }
            else if(strncmp(text,"if",2)==0 && !(*(text+3)=='_' || isalnum(*(text+3)))){
                create_token("if",IF,line);
                strcpy(buffer,"");
                text+=2;
            }
            else if(strncmp(text,"else",4)==0 && !(*(text+5)=='_' || isalnum(*(text+5)))){
                create_token("else",ELSE,line);
                strcpy(buffer,"");
                text+=4;
            }
            else if(strncmp(text,"struct",6)==0 && !(*(text+7)=='_' || isalnum(*(text+7)))){
                create_token("struct",STRUCT,line);
                strcpy(buffer,"");
                text+=6;
            }
            else if(strncmp(text,"typedef",7)==0 && !(*(text+8)=='_' || isalnum(*(text+8)))){
                create_token("typedef",TYPEDEF,line);
                strcpy(buffer,"");
                text+=7;
            }
            else if(strncmp(text,"enum",4)==0 && !(*(text+5)=='_' || isalnum(*(text+5)))){
                create_token("enum",ENUM,line);
                strcpy(buffer,"");
                text+=4;
            }
            else if(isdigit(*text)){
                strcpy(buffer,"");
                while(isdigit(*text)){
                strncat(buffer,text,1);
                text++;   
                }

            create_token(buffer,NUM_LITERAL,line);
            }
            //identifier
            else{
                strcpy(buffer,"");
                if(!(isalpha(*text) || *text=='_')){
                    printf("\nLos naziv identifiera\n");
                    exit(1);
                }
                while(isalnum(*text) || *text=='_'){
                    strncat(buffer,text,1);
                    text++;
                }
                create_token(buffer,IDENTIFIER,line);
            }
            break;
            
        
        }   
    }                
}
void tokens_print(void){

    // Token (int line, char* lexeme...)
    // vector (gomila Token* -> void*)
    // cast void* -> Token*
    // print Token->lexeme
    for(int i=0;i<tokens->size;i++){
        Token* t = tokens->data[i];
        printf("%s\t",t->word);
    }
    puts("");
}