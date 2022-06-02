#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN_STR 20


struct gates
{	
    char *input;
    char recognition[LEN_STR], output, gate_type;


};
struct gates *allof_Struct;

       struct gates getData(char type, char inp[], char reg[])
	{
    	struct gates curent_Gate;

    	curent_Gate.gate_type = type;
    	curent_Gate.input = malloc(strlen(inp) + 1);
    
    	strcpy(curent_Gate.input, inp);
    	strcpy(curent_Gate.recognition, reg);
    
    		return curent_Gate;
	};
	/* */

char getout_Gate(char recognition[], int size)
{
    int i=1;			/* TEST PURPOSES */
    while(i){
       
         if(i==size) break;
        if (strcmp(allof_Struct[i].recognition, recognition) == 0)
            return allof_Struct[i].output;
            i++;
     	}
}

/*Remove spaces to make a character array entry for easy indexing */
void Spaces(char* str) {
    
    char* chr = str;
   /* MAIN LOOP */
   do{
       if(*chr == ' ')  ++chr;
      
    } while (*str++ = *chr++);
   
}
void generate_GateOutPut(int size)
{
    int i=1;
    while(i)
    {
        if(i==size) break;
        bool pas0 = false;
        char *input = malloc(strlen(allof_Struct[i].input)+2);
        
        	strcpy(input, allof_Struct[i].input);
        
        char *tokens = NULL;
        char ch, ch2;
        
        if (allof_Struct[i].gate_type=='A')
        {
    
            /* produce output according to logic AND logic*/
            pas0 = true;
            tokens = strtok(input, " ");
            while (tokens != NULL)
            {
                ch = getout_Gate(tokens, size);
                if (ch == '1')
                {
                    pas0 = true;
                }
                else
                {
                    pas0 = false;
	    }
                tokens = strtok(NULL, " ");
            /* printf("TEST");*/
            }
            allof_Struct[i].output = pas0 ? '1' : '0';
         }
         else if(allof_Struct[i].gate_type== 'O'){
            /* produce output according to logic OR logic*/
            
            pas0 = false;
            tokens = strtok(input, " ");
            
            while (tokens != NULL)
            {
                ch = getout_Gate(tokens, size);
                if (ch == '1')
                {
                    pas0 = pas0 || true;
                }
                else
                {
                    pas0 = pas0 || false;
                }
                tokens = strtok(NULL, " ");
            }
 
            allof_Struct[i].output = pas0 ? '1' : '0';
            }
         else if(allof_Struct[i].gate_type== 'N'){
            /* produce output according to logic NOT logic*/
            
            pas0 = true;
            ch = getout_Gate(input, size);
            if (ch == '1')
            {
                pas0 = !pas0;
            }
            else
            {
                pas0 = pas0;
            }
            allof_Struct[i].output = pas0 ? '1' : '0';
            }
         else if(allof_Struct[i].gate_type== 'F'){
            /* produce output according to logic FLİPFLOP logic*/
            
            pas0 = true;
            ch = getout_Gate(input, size);
            ch2 = allof_Struct[i].output;
            if (ch == '0')
            {
                if (ch2 == '0')
                {
                     pas0 = false;
                }
                else
                {
                     pas0 = true;
                }
            }
            else
            {
                if (ch2 == '0')
                {
                    pas0 = true;
                }
                else
                {
                    pas0 = false;
                }
            }

            allof_Struct[i].output = pas0 ? '1' : '0';
         }
      
        
        free(input);
        free(tokens);
        i++;
    }
}
/*Search the output of each door using recognition*/

int main()
{
    size_t x = 20;

    int i = 0, y=20;
    
     allof_Struct = malloc(sizeof(struct gates)*y);

    FILE *fptr;
    fptr = fopen("circuit.txt", "r");
    
    char *input ,gate_type;
    size_t length = 0,readfile;
    char *pas0 ,*pas1 ,*inputcpy ;
 
    while ((readfile = getline(&input, &length, fptr)) != EOF)
    {
        if(input[strlen(input)-1] = '\n')
        {
            input[strlen(input)-1] = '\0';
        }
        else
        {
            input[strlen(input)] = '\0';
        }

        if (i == y - 2)
        {
            y =y + x;
           if (!(allof_Struct = realloc(allof_Struct,  sizeof(struct gates)*y))) /*Reserving memory if the current memory is almost full*/
              
                exit(0);
              
        }
        /*check if the line is the input line */
        if (strstr(input, "INPUT"))
        {

            char *gate_input = (char *)malloc(strlen(input) + 2);

            char *copy = strstr(input, "INPUT") + strlen("INPUT") + 1;
            strcpy(gate_input, copy);
            char *s = strtok(gate_input, " ");
            while (s != NULL)
            {

                allof_Struct[i++] = getData('L', "I", s);
                if (i == y - 2)
                {
                    y = y +x;
                  if (!(allof_Struct = realloc(allof_Struct,  sizeof(struct gates)*y)))  exit(0);
                    
                }
                if (s != NULL)
                    
                s = strtok(NULL, " ");
            }
            free(s);
            free(gate_input);
            
        }
        // the line is the door, so build the doors and add them to the tree, the doors that are connected to others should appear under the tree
        else
        {
            
            inputcpy = malloc(strlen(input)+3);
            strcpy(inputcpy, input);
            inputcpy = strstr(inputcpy, " ") + 1;
            pas0 = malloc(strlen(inputcpy));
            int j = 0;
            while (inputcpy[j] != ' ')
            {
                pas0[j] = inputcpy[j];
                j++;
            }
            pas0[j] = '\0';
            pas1 = malloc(strlen(inputcpy) + 4);
            pas1 = strstr(inputcpy, " ") + 1;
            
          /*and or etc. sorting and assigning data by*/
            if (strstr(input, "AND"))
            {
           
              allof_Struct[i++] = getData('A', pas1, pas0);
            }
            
           
            else if (strstr(input, "FLIPFLOP"))
            {
                allof_Struct[i++] = getData('F', pas1, pas0);
                allof_Struct[i - 1].output = '0';
            }
            else if (strstr(input, "NOT"))
            {
            
                allof_Struct[i++] = getData('N', pas1, pas0);
            }
            
            else if (strstr(input, "OR"))
            {
            
                allof_Struct[i++] = getData('O', pas1, pas0);
            }
        }
    }
    
    fclose(fptr);
    free(input);
    
    FILE *iptr;
    iptr = fopen("input.txt", "r");
   
    
    // each door gates without read line, can\'t start digits(input), output calcualte
    
   
    while ((readfile = getline(&input, &length, iptr)) != EOF)
    {
        Spaces(input);
        int j = 0,k=0;
        //Setting the gateless input values
        for ( k = 0; k < i; k++)
        {
            if (allof_Struct[k].gate_type == 'L')
            
                allof_Struct[k].output = input[j++];
                
            
        }
        generate_GateOutPut(i);
        //The last exit is the exit of the last door
        printf("%c\n", allof_Struct[i - 1].output);
    }
    fclose(iptr);
 
 return 0;
    
}




