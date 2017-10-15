/////////////////////////////////


#include "str.c"
#include "variables.c"
#include "lltable.c"
#include "stack.c"


/////////////////////////////////

// ======================================================================
//  PRECEDENCNI SYNTAKTICKA ANALYZA
// =====================================================================

/*
*	@function getToken
*/
int readNextToken = 1;
token * getToken() {
	token *t = tok;
	printf("--- getToken()\n");
	if (readNextToken) {
		printf("--- NEXT ()\n");
    	t = get();
	} else {
		printf("--- PAUSE ()\n");
		readNextToken = 1;
	}
	
	return t;
}

void tokenPause() {
	readNextToken = 0;
}


/*
*	@function readExpression
*	@param int typeA
*	@param int typeB
*/
int expeRetype(int typeA, int typeB) {
	switch (typeA) {
        case TYPE_INT_DATA:
            switch (typeB) {
                case TYPE_INT_DATA:
                	return TYPE_INT_DATA;			// int a int, musi byt int
                                			
                case TYPE_DOUBLE_DATA:
                    return TYPE_DOUBLE_DATA;		// int a dbl, musi byt dbl
			}
		break;
			
		case TYPE_DOUBLE_DATA:
			switch (typeB) {
				case TYPE_DOUBLE_DATA:
					return TYPE_DOUBLE_DATA;		// dbl a dbl, musi byt dbl

				case TYPE_INT_DATA:
					return TYPE_DOUBLE_DATA;		// dbl a int, musi byt dbl
			}
		break;
									
		case TYPE_STRING_DATA: 
			switch (typeB) {
				case TYPE_STRING_DATA:
					return TYPE_STRING_DATA;		// str a str, musi byt str
			}				
		break;
	}
	
	return 0;
}

tabItem *getID() {
	token 	*temp;
	
	temp 	= tok;
	tok 	= get();
	
	printf(">>>>> GET ID <<<<<<");
	if (tok->type == TYPE_DOT) {
		tabItem *classItem = search_HashTable(table_class, tok->attribute);
		if (classItem->table) {
			tok = get();
			return search_HashTable(classItem->table, tok->attribute);
		} else {
			return NULL;
		} 
	} else {
		tokenPause();
		return search_HashTable(func_save->table, temp->attribute);
	}

	return NULL;
}

/*
*	@function setExpressionVar
*	@param tStack *s
*	@param token *tok
*	@param tabItem **newVariableInfo
*
*/
int setExpressionVar(tStack *s, token *tok, tabItem **newVariableInfo) {
	int result;

	switch(tok->type) {
		case TYPE_ID: 			 	// nacteny token je identifikator, zjistim si adresu jeho dat
			printf("EXPR setExpressionVar() ID\n");
			if(((*newVariableInfo) = getID()) == NULL ) {
				SDispose(s);
				
				return ERR_SEM;
			}
		break;
				    
		case TYPE_INT_DATA: 
			printf("EXPR setExpressionVar() INT\n");

			if((result = insertVarInt(atoi(tok->attribute), newVariableInfo))) {
				printf("EXPR ERR");
		        SDispose(s);
		        return result;
		    }
	    
	    break;
	                
		case TYPE_DOUBLE_DATA: 
			printf("EXPR setExpressionVar() DBL\n");
			if((result = insertVarDbl(atof(tok->attribute), newVariableInfo))) {
				printf("EXPR ERR");
	        	SDispose(s);
	            return result;
	        }
	        
	    break;
	                	                
	    case TYPE_STRING_DATA: 
	    	printf("EXPR setExpressionVar() STR\n");
			if((result = insertVarStr(tok->attribute, newVariableInfo))) {
				printf("EXPR ERR");
	            SDispose(s);
	            return result;
	        }
	    break;
	        
		default: 
	        newVariableInfo = NULL;
	        printf("EXPR setExpressionVar(Tok->type :: %i) DEF\n", tok->type);
	}

	return 0;
}

/*
*	@function readExpression
*	@param tabItem *ret		// Item s návratovou hodnotou
*	@param tabItem *item	// Poslední item
*	@param tabItem *output	// Output
*
*/
int readExpression(tabItem *ret, token *tokenTemp, tabItem *output) {
	

    tStack_item a;
    tStack_item b;   
    tStack_item d;
    tStack_item k;
    tStack_item m;
    tStack_item n;
    tStack_item f;
    tStack_item c;
    tStack s;
 
 	// Retype return
    switch(ret->typeData) {
    	case TYPE_INT:     ret->typeData = TYPE_INT_DATA;break;
    	case TYPE_DOUBLE:  ret->typeData = TYPE_DOUBLE_DATA;break;
    	case TYPE_STRING:  ret->typeData = TYPE_STRING_DATA;break;
    }

	printf("************************ READ EXPRESION ************************ \n");
	printf(" >>> RET (INT 39 | DBL 40 | STR 41) = %i\n", ret->typeData);

 	TbSmHash = init_HashTable(10);

    SInit(&s);      			// Inicializace zasobniku

  	SPush(&s, PA_LT, NULL);  	// vlozim na zasobnik $ - zarazka

	tabItem *newVariableInfo;

	int term, result;
	
	if (tokenTemp == NULL) {
		
		printf("EXPR NULL\n");
		tok 			= getToken();
		result 			= setExpressionVar(&s, tok, &newVariableInfo);
		a.type			= isID(tok->type);		// Ulozim si typ tokenu

	} else {
		
		printf("EXPR TOK type::%i attr::%s\n", tokenTemp->type, tokenTemp->attribute);
		result 			= setExpressionVar(&s, tokenTemp, &newVariableInfo);
		a.type			= isID(tokenTemp->type);		// Ulozim si typ tokenu
		tokenPause();
	}

 	if (result) return result;
 		
 	do {

 		printf("EXPR IN DO\n");

    	b = STop_Term(&s);      	//znak ze zasobniku
    	
    	int _table = getTable(b.type, a.type);

    	printf("DO SWITCH LL TABLE A(%i) = B(%i) => %i\n", b.type, a.type, _table);

    	switch (_table) {  //vyber clena z tabulky
    
			////////////////////////////////////////////////////////////////////
			//
			//	= : push(A) & pøeèti další symbol A ze vstupu
			//
			////////////////////////////////////////////////////////////////////
      		
			case PA_ASSIG: // =
      			printf("GET LL TABLE - TYPE_ASSIG A(%i) = B(%i)\n", b.type, a.type);
        		SPush(&s, a.type, newVariableInfo);
        		
        		b 		= STop_Term(&s);    		// kvuli (i)

        		tok 	= getToken();

		        a.type 	= isID(tok->type);

		        result 	= setExpressionVar(&s, tok, &newVariableInfo);
		        
				if (result) return result;
		        
		    break;
			       
			////////////////////////////////////////////////////////////////////
			//
			//	< : zamìò vrcholZasobniku b za b < na zásobníku &
			//	push(vstupni token) & pøeèti další symbol a ze vstupu
			//
			////////////////////////////////////////////////////////////////////
      
	  		case PA_LESS: // <
	  		
	  			printf("GET LL TABLE - TYPE_LESS A(%i) < B(%i)\n", b.type, a.type);

	      		term = SFind_Term(&s);         			// najde pozici terminalu

	      		SPush_term(&s, PA_LESS, term);  		// za terminal da <

				SPush(&s, a.type, newVariableInfo);		// na zasobnik da token

			    tok 	= getToken();

				a.type 	= isID(tok->type);

				result 	= setExpressionVar(&s, tok, &newVariableInfo);


				printf("EXPR TOK - TYPE_LESS result: %i\n", result);

		        if (result) return result;
	          	          
	      		b = STop_Term(&s);  					// do b da terminal
	      		
      		break;
 
			////////////////////////////////////////////////////////////////////
			//
			//	> : IF <y je na vrcholu zásobníku AND r: A › y ? P
			//		THEN zamìò <y za A & vypiš r na výstup ELSE chyba
			//
			////////////////////////////////////////////////////////////////////
			
    		case PA_GREAT: 							// >

      			printf("GET LL TABLE - TYPE_GREAT A(%i) > B(%i)\n", b.type, a.type);

				d = STop(&s);       					// vezmu vrchol a na zasobniku a podle nej delam switch
      			
      			printf (" > STOP Type = %i\n", d.type);

      			switch (d.type) {
      				
        			case PA_ID:						// redukce podle E->i
        				printf("::: TYPE_ID\n");

        				SPop(&s);  						// z vrcholu zasobniku zahodime identifikator
        				f = STop(&s);  					// nacteme vrchol zasobniku, kde by mel byt '<'
        				
        				if (f.type == PA_LESS) { 		// <
        
        					printf("::: TYPE_ID ::: LESS\n");
          					SPop(&s); 					// zahodime z vrcholu zasobniku <
          					
          					if (d.data == NULL) {
              					SDispose(&s);
                        		return ERR_SEM;
          					}				 			
          					
          					SPush(&s, PA_E, d.data);// na zasobnik dame zredukovanou promennou na E a jeji adresu s daty		

          					output = d.data;  			// na vystup, readExpression
          					printf("\n 1-PA - OUTPUT \n");
          					check_item(output);
        				}

        			break;
 
        			case TYPE_RIGHT_BRACKET: 			// ) ~ redukce dle pravidla: E->(E)		
        				printf("::: TYPE_RIGHT_BRACKET\n");

        				SPop(&s);    					// odstranim )
				        c = STop(&s);  					// nacteme vrchol zasobniku - nejake E
				        SPop(&s);    					// odstranim E
				        SPop(&s);    					// odstranim (
				        SPop(&s);    					// odstranim <
				        SPush(&s, PA_E, c.data);
				        output = c.data;  				// ulozim na vystup
				        printf("\n 2-PA - OUTPUT \n");
          				check_item(output);
			        
			        break;
 
        			case PA_E:
        				printf("::: TYPE_PTE\n");
				        c = STop(&s);  					// nacteme vrchol zasobniku, nejake E
				        SPop(&s);   					// odstranime vrchol zasobniku
				        k = STop(&s); 					// nacteme vrchol zasobniku - operaci
				        
        				if (isOperations(k.type)) { 	// jedna se o operaci

        					printf("IS OPERATION %i \n", k.type);

					        SPop(&s);  						// odstranime  z vrcholu zasobniku operaci
					        m = STop(&s);  					// nacteme vrchol zasobniku, melo by byt E
					        SPop(&s);   					// odstranime vrchol
					        n = STop(&s); 					// nacteme dalsi, melo by byt <


					        if (m.type == PA_E && n.type == PA_LESS) {		//pokud sme nacetli <E
	          					
	          					printf("IS OPERATION GOOOO \n");
		            			SPop(&s); 						// odstranime z vrcholu zasobniku <
					            

								string newVar;					// generujeme promennou, kde ulozime vysledek operace
								
					            if (strInit(&newVar)) {
					                SDispose(&s);
					                strFree(&newVar);
					                return ERR_INSIDE;
					            }
					            
		            			if (generateVariable(&newVar)) {
					                SDispose(&s);
					                strFree(&newVar);
		                            return ERR_INSIDE;
		            			}

		            			tabItem *item   	= create_tabItem();
							 	tabItem *vysledek 	= create_tabItem();

							 	item->name 			= strGetStr(&newVar);
							 	item->typeData		= TYPE_INT_DATA;

							    insert_into_HashTable(TbSmHash, item);
								printf("\n name %s\n", strGetStr(&newVar));

		            			vysledek = search_HashTable(TbSmHash, strGetStr(&newVar));

		            			printf("\n 2-PA - VYSLEDEk \n");
          						
		            			//strFree(&newVar);
		 
		            			switch(k.type) { 				// a podle typu operace provedeme vhodnou instrukci
		            				
									////////////////
		            				// ARYTHMETIC
		            				
		              				case TYPE_ADD:				// operace scitani
		              				case TYPE_SUB:				// operace odcitani
			              			case TYPE_MUL:				// operace nasobeni
		             			 	case TYPE_DIV:				// operace deleni

			                            if (!(vysledek->typeData = expeRetype(m.data->typeData, c.data->typeData))) {  // pøetypování výsledku
			                            	return ERR_SEM;
										}

		 							////////////////
		            				// COMPARSION
		              				case TYPE_GREAT:
		              				case TYPE_LESS:
		              				case TYPE_LESS_OR_EQ:
		              				case TYPE_GREAT_OR_EQ:
		              				case TYPE_ASSIG:
		              				case TYPE_NOT_EQUAL:			
		              					

		              					printf("GENERATE INSTRUCTION :: %i\n", k.type);

			              				generateInstruction(k.type, m.data, c.data, vysledek);

			              				SPush(&s, PA_E, vysledek);

		              					output 	= vysledek;
		              					
		              					
          								check_item(output);

		              					b = STop_Term(&s);
		              				break;
						 
						            default:
						                SDispose(&s);
						                return ERR_SYN;
						            break;
		            			}
		          			}
	        			}
        			break;
 
        			default:
        				printf("EXPR ERR SYN (%i)\n", _table);
                    	SDispose(&s);
          				return ERR_SYN;
        			break;
      			}
      		break;
 
      		default:
                SDispose(&s);
        		return ERR_SYN;
      		break;
 
    		case PA_ERROR:
      			if (a.type == PA_LT && b.type == PA_LT) {
                	return ERR_SYN;
      			}
      			else if (tok->type == TYPE_SEMICOLON || tok->type == TYPE_COMMA || tok->type == TYPE_RIGHT_BRACKET) {
          			SDispose(&s);
        			return ERR_OK;
     			} else {
          			SDispose(&s);
                	return ERR_SYN;
      			}
    		break;
    	}
  	} while (a.type != PA_LT || b.type != PA_LT);
  	
  	if (a.type == PA_LT && b.type == PA_LT)
    	SDispose(&s);
  		return ERR_OK;
	}