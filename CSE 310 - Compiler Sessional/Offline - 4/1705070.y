%{
#include<bits/stdc++.h>
#include "SymbolTable.cpp"
#include "StringHandler.h"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;

extern int numberOfLines;
extern int numberOfErrors;

FILE* logs;
FILE* errors;

SymbolTable symbolTable(30);
map<string, string> SymbolSet;
vector< pair<string,string> >temp_param_list;
vector< pair<string,string> >arg_param_list;
vector<SymbolInfo*>v;
vector< pair<string,string> >decld_var_carrier;   //vector for adding the variables to the assembly CODES
vector< pair<string,string> >var_carrier;
vector< pair<string,string> >decld_f_var;         //vector for the declared variables inside the function to push the variables to the STACK

string type_of_var, statement_solver, return_type_solver, running_f_name = "", scope_holder = "";
bool is_func = false;
int control_arg, scope_counter = 1, scope_counter_2 = 0;

/* ******************* */
/*       Output        */
/* 	    Procedure      */
/* ******************* */
string output_procedure ="\nPRINT_INT PROC\
						\n\tPUSH AX\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\n\n\tOR AX, AX\
						\n\tJGE END_IF1\
						\n\tPUSH AX\
						\n\tMOV DL,'-'\
						\n\tMOV AH, 2\
						\n\tINT 21H\
						\n\tPOP AX\
						\n\tNEG AX\
						\n\nEND_IF1:\
						\n\tXOR CX, CX\
						\n\tMOV BX, 10D\
						\n\nREPEAT1:\
						\n\tXOR DX, DX\
						\n\tDIV BX\
						\n\tPUSH DX\
						\n\tINC CX\
						\n\n\tOR AX, AX\
						\n\tJNE REPEAT1\
						\n\n\tMOV AH, 2\
						\n\nPRINT_LOOP:\
						\n\tPOP DX\
						\n\tOR DL, 30H\
						\n\tINT 21H\
						\n\tLOOP PRINT_LOOP\
						\n\tMOV AH, 2\
						\n\tMOV DL, 10\
						\n\tINT 21H\
						\n\n\tMOV DL, 13\
						\n\tINT 21H\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP AX\
						\n\tRET\
						\nPRINT_INT ENDP\n\n";

// error detection
void yyerror(const char *s){
	numberOfErrors++;
    fprintf(errors, "Line no %d: %s\n", numberOfLines, s);
}

void symbolSet(){
    SymbolSet["comma"] = ",";
	SymbolSet["semicolon"] = ";";
	SymbolSet["left_third"] = "[";
	SymbolSet["right_third"] = "]";
	SymbolSet["newline"] = "\n";
	SymbolSet["left_first"] = "(";
	SymbolSet["right_first"] = ")";
	SymbolSet["equal"] = "=";
	SymbolSet["plus"] = "+";
	SymbolSet["minus"] = "-";
	SymbolSet["left_curl"] = "{";
	SymbolSet["right_curl"] = "}";
	SymbolSet["incop"] = "++";
	SymbolSet["decop"] = "--";
}

// get it
string getFromSymbolSet(string name){
	return SymbolSet.at(name);
}
%}

%union{
    SymbolInfo* symbolInfoPointer;
}
%token FOR IF DO INT FLOAT VOID COMMA SEMICOLON
%token ELSE WHILE DOUBLE CHAR RETURN CONTINUE
%token PRINTLN  ASSIGNOP LPAREN RPAREN
%token LCURL RCURL LTHIRD RTHIRD
%token<symbolInfoPointer>CONST_INT
%token<symbolInfoPointer>CONST_FLOAT
%token<symbolInfoPointer>CONST_CHAR
%token<symbolInfoPointer>ADDOP
%token<symbolInfoPointer>MULOP
%token<symbolInfoPointer>LOGICOP
%token<symbolInfoPointer>BITOP
%token<symbolInfoPointer>RELOP
%token<symbolInfoPointer>INCOP
%token<symbolInfoPointer>DECOP
%token<symbolInfoPointer>ID
%token<symbolInfoPointer>NOT

%type <symbolInfoPointer> expression logic_expression simple_expression rel_expression  type_specifier term unary_expression variable factor statement expression_statement  compound_statement  declaration_list var_declaration statements func_declaration  func_definition parameter_list unit program argument_list arguments

// This is the starting point of implementation of bison grammar 
%nonassoc LOWER_PREC_THAN_ELSE
%nonassoc ELSE
%left RELOP LOGICOP
%left ADDOP
%left MULOP

%type <symbolInfoPointer>start
%%

start : program {
	fprintf(logs, "Line %d: start : program\n\n\n",numberOfLines-1);
	symbolTable.printAllTable(logs);

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	if(numberOfErrors == 0){

		string first, second, temp = "";
		temp = ".MODEL SMALL\
			\n\n.STACK 100H\
			\n\n.DATA\n";

		for(int i = 0;i<decld_var_carrier.size(); i++){
			first  = decld_var_carrier[i].first;
			second = decld_var_carrier[i].second;

			if(second == ""){
				temp = temp + first + " DW ?\n";
			}else{
				temp = temp + first + " DW "+ 
					second + " dup(?)\n";
			}
		}

		$1->extraSymbolInfo.assm_code = temp + "\n.CODE" + output_procedure + $1->extraSymbolInfo.assm_code;

		ofstream out, optOut;
		out.open("code.asm");
		out << $1->extraSymbolInfo.assm_code;
		optOut.open("optimized_code.asm");
		optOut << optimizer($1->extraSymbolInfo.assm_code);
	}else{
		cout << "Error occurred. Check error.txt file" << endl;
	}
};

program : program unit {
	fprintf(logs, "Line %d: program : program unit\n\n", numberOfLines);
	$$ -> extraSymbolInfo.stringAdder(getFromSymbolSet("newline") + $2 -> extraSymbolInfo.stringConcatenator);
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code + $2->extraSymbolInfo.assm_code;
	} | unit {
	fprintf(logs, "Line %d: program : unit\n\n", numberOfLines);
	$$ -> extraSymbolInfo.stringConcatenator = $1 -> extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
};

unit : var_declaration{
	fprintf(logs, "Line %d: unit : var_declaration\n\n", numberOfLines);
	$$ -> extraSymbolInfo.stringConcatenator = $1 -> extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | func_declaration{
	fprintf(logs, "Line %d: unit : func_declaration\n\n", numberOfLines);
	$$ -> extraSymbolInfo.stringConcatenator = $1-> extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | func_definition{
	fprintf(logs, "Line %d: unit : func_definition\n\n", numberOfLines);
	$$ -> extraSymbolInfo.stringConcatenator = $1-> extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
};

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{

	/* ************************************************************************ */
	/*	We need to check some properties of function declaration in this step:  */
	/*           		1. Check return type is same                            */
	/*      		 2. Check number of parameter is same                       */
	/*         	      3. Check parameter sequence is same                       */
	/*       	      4. No void Parameters are declared                        */
	/* ************************************************************************ */

	fprintf(logs, "Line %d: func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n\n", numberOfLines);
	SymbolInfo* temp = symbolTable.LookUp($2->getName());

	// if it found in symbol table
	if(temp != 0){

		// Checking return type
		if(temp->extraSymbolInfo.returnTypeOfFunction != $1->getType()){
			numberOfErrors++;
			fprintf(errors, "Error at line %d : Return Type Mismatch of function declaration\n\n", numberOfLines);
		}

		// Checking parameter
		if(temp->extraSymbolInfo.functionParamList.size()!=temp_param_list.size()){
			numberOfErrors++;
			fprintf(errors, "Error at line %d: Unequal number of parameters\n\n", numberOfLines++);
			temp_param_list.clear();
		}
		// Checking parameter sequence
		else{
			for(int i=0;i<temp_param_list.size();i++){
				if(temp_param_list[i].second != temp->extraSymbolInfo.functionParamList[i].second){
					numberOfErrors++;
					fprintf(errors, "Argument Type Mismatch with previous function declaration \n\n", numberOfLines);
				}
			}
			temp_param_list.clear();
		}
	}
	// if not found in symbol table
	else{
		// variable to check void type
		bool isVoid = false;
		// checking no void parameter is declared
		for(int i=0;i<temp_param_list.size();i++){
			if(temp_param_list[i].second=="VOID"){
				isVoid = true; 
				break;
			}
		}
		SymbolInfo* temp = new SymbolInfo();
		temp->extraSymbolInfo.typeOfID = "FUNCTION";
		temp->extraSymbolInfo.returnTypeOfFunction = $1->getType();
		temp->extraSymbolInfo.isFunction = true;
		temp->extraSymbolInfo.isFunctionDeclared = true;
		temp->setName($2->getName());
		temp->setType($2->getType());

		if(isVoid){
			numberOfErrors++;
			fprintf(errors, "Error at line %d: Parameter cannot be void \n\n", numberOfLines);
			temp->extraSymbolInfo.isFunction = false;
		}
		for(int i=0;i<temp_param_list.size();i++){
			temp->extraSymbolInfo.functionParamList.push_back(make_pair(temp_param_list[i].first, temp_param_list[i].second));
		}
		temp_param_list.clear();
		symbolTable.InsertModified(temp);
	}
	$$ -> extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator + $2->getName()+getFromSymbolSet("left_first")+$4->extraSymbolInfo.stringConcatenator+getFromSymbolSet("right_first")+getFromSymbolSet("semicolon");
	fprintf(logs, "%s\n\n\n", $$->extraSymbolInfo.stringConcatenator.c_str());
} | type_specifier ID LPAREN RPAREN SEMICOLON {
	fprintf(logs, "Line %d: func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n\n", numberOfLines);
	SymbolInfo* temp = symbolTable.LookUp($2->getName());
	if(temp != 0){
		if(temp->extraSymbolInfo.returnTypeOfFunction != $1->getType()){
			numberOfErrors++;
			fprintf(errors, "Error at Line %d: Return Type Mismatch of function declaration \n\n", numberOfLines);
		}
		if(temp->extraSymbolInfo.functionParamList.size()!=0){
			numberOfErrors++;
			fprintf(errors, "Error at Line %d : Unequal number of parameters\n\n", numberOfLines);
			temp_param_list.clear();
		} }else{
			SymbolInfo* temp = new SymbolInfo();
			temp->extraSymbolInfo.typeOfID = "FUNCTION";
			temp->extraSymbolInfo.returnTypeOfFunction = $1->getType();
			temp->extraSymbolInfo.isFunction = true;
			temp->extraSymbolInfo.isFunctionDeclared = true;
			temp->setName($2->getName());
			temp->setType($2->getType());

			for(int i=0;i<temp_param_list.size();i++){
				temp->extraSymbolInfo.functionParamList.push_back(make_pair(temp_param_list[i].first, temp_param_list[i].second));
			}
			temp_param_list.clear();
			symbolTable.InsertModified(temp);
		}
		$$ -> extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator + $2->getName()+getFromSymbolSet("left_first")+getFromSymbolSet("right_first")+getFromSymbolSet("semicolon");
	fprintf(logs, "%s\n\n\n", $$->extraSymbolInfo.stringConcatenator.c_str());
};

func_definition : type_specifier ID LPAREN parameter_list RPAREN{
		scope_counter = scope_counter + 1;
		fprintf(logs, "Line %d: func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n", numberOfLines);
		SymbolInfo *s = symbolTable.LookUp($2->getName());
		SymbolInfo *temp = new SymbolInfo();
		bool flag = true;
		// if it doest not exixts in any scope then insert the ID into
		if(s==0){
			bool check = false;
			for(int i=0;i<temp_param_list.size();i++){
				if(temp_param_list[i].second == "VOID"){
					check = true;
				}
			}

			// make a new object to insert into Symbol Table
			temp->extraSymbolInfo.typeOfID = "FUNCTION";
			temp->extraSymbolInfo.returnTypeOfFunction = $1->getType();
			temp->extraSymbolInfo.isFunction = true;
			temp->extraSymbolInfo.isFunctionDefined = true;
			temp->setName($2->getName());
			temp->setType($2->getType());

			if(check){
				numberOfErrors++;
				fprintf(errors, "Error at line %d : Parameter cannot be VOID\n\n", numberOfLines);
				temp->extraSymbolInfo.isFunction=false;
			}

			for(int i=0;i<temp_param_list.size();i++){
				temp->extraSymbolInfo.functionParamList.push_back(make_pair(temp_param_list[i].first, temp_param_list[i].second));
				temp->extraSymbolInfo.modfd_param_list.push_back(temp_param_list[i].first+to_string(scope_counter));              
				// pushing to the modified paramater list of the pointer
			}

			/*if(return_type_solver!=$1->getType())
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
				return_type_solver="";
				temp->extraSymbolInfo.isFunction=false;
			}*/
			symbolTable.InsertModified(temp);
			//temp_param_list.clear();
		}
		// if it already exists in global scope
		else{
			// function already exists
			if(s->extraSymbolInfo.isFunctionDefined){
				numberOfErrors++;
				fprintf(errors, "Error at line %d: Multiple definition of function\n\n", numberOfLines);
				temp_param_list.clear();
			}else if(s->extraSymbolInfo.isFunctionDeclared){
				/* Three case to handle here 
				1. Return type check 
				2. Check number of parameters and
				3. Check for sequence of parameters */
				s->extraSymbolInfo.isFunctionDefined = true;
				string actReturnType = $1->getType();
				string declaredReturnType = s->extraSymbolInfo.returnTypeOfFunction;
				int declaredParamSize = s->extraSymbolInfo.functionParamList.size();
				int definedParamSize = temp_param_list.size();

				// Case 1: Return type Check
				if(actReturnType != declaredReturnType){
					numberOfErrors++;
					fprintf(errors, "Error at line %d: Return type mismatch\n\n", numberOfLines);
					flag = false;
				}
				// Case 2: Check for size of paramter list
				else if(definedParamSize != definedParamSize){
					numberOfErrors++;
					fprintf(errors, "Error at line %d: Unequal number of parameters\n\n", numberOfLines);
					temp_param_list.clear();
					flag = false;
				}
				// Case 3: Check for sequence of parameter list 
				else{
					for(int i = 0;i<temp_param_list.size();i++){
						if(temp_param_list[i].second != s->extraSymbolInfo.functionParamList[i].second){
							numberOfErrors++;
							fprintf(errors, "Error at line %d: Argument Type Mismathch with function declaration\n\n", numberOfLines);
							flag=false;
							break;
						}
					}
					// temp_param_list.clear();
					for(int i =0;i<temp_param_list.size();i++)
					{
						s->extraSymbolInfo.modfd_param_list.push_back(temp_param_list[i].first+to_string(scope_counter));               //pushing to the modified paramater list of the pointer
					}
				}
				if(return_type_solver!=$1->getType())
				{

					numberOfErrors++;
					fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
					return_type_solver="";
					flag=false;
				}
			}
		}
		// $$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+$2->getName()+getFromSymbolSet("left_first")+$4->extraSymbolInfo.stringConcatenator+getFromSymbolSet("right_first")+$6->extraSymbolInfo.stringConcatenator;
		//fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

		/* ******************* */
		/*      ICG Code       */
		/* ******************* */
		running_f_name = $2->getName(); //saving the name to be used during returning
		decld_var_carrier.push_back(make_pair(running_f_name+"_return_val", ""));  //saving the variable in the .DATA segment of asm file
}compound_statement{
	fprintf(logs, "Line %d: func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n", numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+$2->getName()+getFromSymbolSet("left_first")+$4->extraSymbolInfo.stringConcatenator+getFromSymbolSet("right_first")+$7->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	if($2->getName() == "main"){
		$$->extraSymbolInfo.assm_code += "MAIN PROC\
								\n\tMOV AX, @DATA\
								\n\tMOV DS, AX\n";
		$$->extraSymbolInfo.assm_code += $7->extraSymbolInfo.assm_code;
		$$->extraSymbolInfo.assm_code += "\nLABEL_RETURN_";
		$$->extraSymbolInfo.assm_code += running_f_name;
		$$->extraSymbolInfo.assm_code += ":\n+\n\tMOV AH, 4CH\
								\n\tINT 21H\
								\nEND MAIN";
	}else{
		string temp_code = $2->getName()+" PROC\
						\n\tPUSH AX\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\n\n";

		/*---we lookup the func_id to access the parameter list---*/
		SymbolInfo* s = symbolTable.LookUp($2->getName());
		string hold = "";
		stack<string>s1;
		stack<string>s2;

		/*---we push the parameters of the function to the stack of assm_code---*/
		for(int i=0;i<s->extraSymbolInfo.functionParamList.size();i++){
			hold = s->extraSymbolInfo.functionParamList[i].first+to_string(scope_counter);
			temp_code += "\tPUSH "+hold+"\n";
			s1.push(hold);
		}
		temp_code += "\n";
		scope_holder = "";

		/*---we push the declared variables of the function scope inside the stack of assm_code---*/
		for(int i=0;i<decld_f_var.size();i++){
			hold = decld_f_var[i].first;
			temp_code += "\tPUSH "+hold+"\n";
			s2.push(hold);
		}
		decld_f_var.clear(); //clearing the list so that we would not get any weird variables

		temp_code += "\n"+$7->extraSymbolInfo.assm_code+"LABEL_RETURN_"+running_f_name+":\n";

		/*---we pop the parameters of the function from the stack of assm_code---*/
		while (!s2.empty()){
		temp_code += "\tPOP "+s2.top()+"\n";
		s2.pop();
		}
		temp_code += "\n";

		/*---we pop the declared variables of the function from the stack of assm_code---*/
		while (!s1.empty()){
		temp_code += "\tPOP "+s1.top()+"\n";
		s1.pop();
		}

		/*finally we pop the registers from the stack---*/
		temp_code += "\n\tPOP DX\
					\n\tPOP CX\
					\n\tPOP BX\
					\n\tPOP AX\
					\n\tret\n\n";
		temp_code += $2->getName();
		temp_code += " ENDP\n\n";

		/** we set the scope counter to the adjusted value so that next time another f is defined, we get the correct result */
		scope_counter = scope_counter_2;

		$$->extraSymbolInfo.assm_code += temp_code;
	}
} | type_specifier ID LPAREN RPAREN{
	fprintf(logs, "Line %d: func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n", numberOfLines);

	scope_counter++;
	SymbolInfo *s = symbolTable.LookUp($2->getName());

	if(s==0){
		SymbolInfo* temp = new SymbolInfo();
		temp->extraSymbolInfo.typeOfID = "FUNCTION";
		temp->extraSymbolInfo.returnTypeOfFunction = $1->getType();
		temp->extraSymbolInfo.isFunction = true;
		temp->extraSymbolInfo.isFunctionDefined = true;
		temp->setName($2->getName());
		temp->setType($2->getType());

		symbolTable.InsertModified(temp);
	}else{
		if(s->extraSymbolInfo.isFunctionDeclared){
			string actReturnType = $1->getType();
			string funcReturnType = s->extraSymbolInfo.returnTypeOfFunction;

			if(actReturnType != funcReturnType){
				numberOfErrors++;
				fprintf(errors, "Error at line %d: Return type mismatch\n\n", numberOfLines);
				s->extraSymbolInfo.isFunction = false;
			}
		}else if(s->extraSymbolInfo.isFunctionDefined){
			numberOfErrors++;
			fprintf(errors,"Error at Line %d :Multiple defination of function\n\n",numberOfLines);
			temp_param_list.clear();
		}
	}
	//$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+$2->getName()+getFromSymbolSet("left_first")+getFromSymbolSet("right_first")+$5->extraSymbolInfo.stringConcatenator;
	//fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	running_f_name = $2->getName(); //saving the name to be used during returning
	decld_var_carrier.push_back(make_pair(running_f_name+"_return_val", ""));
}compound_statement{
	fprintf(logs,"Line %d: func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+$2->getName()+getFromSymbolSet("left_first")+getFromSymbolSet("right_first")+$6->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*      ICG Code       */
	/*for the main function*/
	/* ******************* */
	
	if($2->getName() == "main"){
		$$->extraSymbolInfo.assm_code += "MAIN PROC\
									\n\tMOV AX, @DATA\
									\n\tMOV DS ,AX\n";
		$$->extraSymbolInfo.assm_code += $6->extraSymbolInfo.assm_code;
		$$->extraSymbolInfo.assm_code += "\nLABEL_RETURN_";
		$$->extraSymbolInfo.assm_code += running_f_name;
		$$->extraSymbolInfo.assm_code += ":\n\n\tMOV AH, 4CH\
									\n\tINT 21H\
									\nEND MAIN";
	}else{
		string temp_code = $2->getName()+" PROC\n";

		/*---pushing the register to the STACK---*/
		temp_code += "\tPUSH AX\
					\n\tPUSH BX\
					\n\tPUSH CX\
					\n\tPUSH DX\n\n";
		string hold = "";
		stack<string>s2;

		/*---we push the declared variables of the function scope inside the stack of assm_code---*/
		for(int i=0;i<decld_f_var.size();i++){
			hold = decld_f_var[i].first;
			temp_code += "\tPUSH "+hold+"\n";
			s2.push(hold);
		}

		decld_f_var.clear(); //clearing the list so that we would not get any weird variables

		temp_code += "\n"+$6->extraSymbolInfo.assm_code;
		temp_code += "LABEL_RETURN_";
		temp_code += running_f_name;
		temp_code += ":\n";

		/*---we pop the parameters of the function from the stack of assm_code---*/
		while (!s2.empty()){
			temp_code += "\tPOP "+s2.top()+"\n";
			s2.pop();
		}

		temp_code += "\n";

		/*finally we pop the registers from the stack---*/
		temp_code += "\n\tPOP DX\
					\n\tPOP CX\
					\n\tPOP BX\
					\n\tPOP AX\
					\n\tret\n\n";

		temp_code += $2->getName()+" ENDP\n\n";
		$$->extraSymbolInfo.assm_code += temp_code;

		/** we set the scope counter to the adjusted value so that next time another f is defined, we get the correct result */
		scope_counter = scope_counter_2;
	}
};

parameter_list  : parameter_list COMMA type_specifier ID
{
		fprintf(logs,"Line %d: parameter_list : parameter_list COMMA type_specifier ID\n\n",numberOfLines);
		temp_param_list.push_back(make_pair($4->getName(),$3->getType()));
		$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+getFromSymbolSet("comma")+$3->extraSymbolInfo.stringConcatenator+$4->getName();
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
}
| parameter_list COMMA type_specifier
{
		fprintf(logs,"Line %d: parameter_list : parameter_list COMMA type_specifier\n\n",numberOfLines);
		temp_param_list.push_back(make_pair("",$3->getType()));
		$$->extraSymbolInfo.stringConcatenator = $1->getName()+getFromSymbolSet("comma")+$3->extraSymbolInfo.stringConcatenator;
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
}
| type_specifier ID
{
		fprintf(logs,"Line %d: parameter_list : type_specifier ID\n\n", numberOfLines);
		temp_param_list.push_back(make_pair($2->getName(),$1->getType()));
		$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator.append($2->getName());
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

}
| type_specifier
{
		fprintf(logs,"Line %d: parameter_list : type_specifier\n\n",numberOfLines);
		temp_param_list.push_back(make_pair("",$1->getType()));
		$$->extraSymbolInfo.stringConcatenator =$1->extraSymbolInfo.stringConcatenator;
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
};

compound_statement : LCURL {
	symbolTable.EnterScope(logs);
	// fprintf(logs,"Line %d: Entering Scope compound_statement LCURL\n\n",numberOfLines);

	scope_counter_2 = symbolTable.getCurrentScopeID();
	scope_holder = to_string(scope_counter_2);

	if(temp_param_list.size()!=0){
		for(int i=0;i<temp_param_list.size();i++){
			string name = temp_param_list[i].first;
			string type = temp_param_list[i].second;

			SymbolInfo *s = new SymbolInfo();
			s->setName(name);
			s->setType("ID");
			s->extraSymbolInfo.typeOfVar = type;
			bool check = symbolTable.InsertModified(s);
			decld_var_carrier.push_back(make_pair(name+to_string(scope_counter),""));
			if(check == 0){
				numberOfErrors++;
				fprintf(errors, "Error at line %d: Duplicate Parameter Name of function\n\n", numberOfLines);
			}
		}
	}
	temp_param_list.clear();
} statements RCURL {
	fprintf(logs,"Line %d: compound_statement : LCURL statements RCURL\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = getFromSymbolSet("left_curl")+"\n"+$3->extraSymbolInfo.stringConcatenator+getFromSymbolSet("right_curl");
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	symbolTable.printAllTable(logs);
	symbolTable.ExitScope(logs);
	$$->extraSymbolInfo.assm_code = $3->extraSymbolInfo.assm_code;
} | LCURL {
	symbolTable.EnterScope(logs);
	// fprintf(logs,"Line %d: LCURL Entering Scope LCURL\n\n",numberOfLines);
	scope_counter_2 = symbolTable.getCurrentScopeID();

	for(int i=0;i<temp_param_list.size();i++){
		string name = temp_param_list[i].first;
		string type = temp_param_list[i].second;

		SymbolInfo *s = new SymbolInfo();
		s->setName(name);
		s->setType("ID");
		s->extraSymbolInfo.typeOfVar = type;
		bool check = symbolTable.InsertModified(s);
		decld_var_carrier.push_back(make_pair(name+to_string(scope_counter), ""));
		symbolTable.printAllTable(logs);
		decld_var_carrier.push_back(make_pair(name+to_string(scope_counter),""));

		if(check == 0){
			numberOfErrors++;
			fprintf(errors, "Error at line %d : Duplicate Parameter Name of function\n\n", numberOfLines);
		}
	}
	temp_param_list.clear();
} RCURL {
	fprintf(logs,"Line %d: compound_statement : LCURL  RCURL\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = getFromSymbolSet("left_curl")+"\n"+getFromSymbolSet("right_curl");
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	symbolTable.printAllTable(logs);
	symbolTable.ExitScope(logs);
};

var_declaration : type_specifier declaration_list SEMICOLON {
	fprintf(logs,"Line %d: var_declaration : type_specifier declaration_list SEMICOLON\n\n",numberOfLines);

	$$->extraSymbolInfo.stringConcatenator = stringAdder(3,$1->extraSymbolInfo.stringConcatenator.c_str(),$2->extraSymbolInfo.stringConcatenator.c_str(),getFromSymbolSet("semicolon").c_str());

	string first, second;
	for(int i = 0; i<var_carrier.size() ; i++){
		first  = var_carrier[i].first;
		second = var_carrier[i].second;

		decld_var_carrier.push_back(make_pair(first+to_string(symbolTable.getCurrentScopeID()),second)); //pushing bacl to vector for assm_code declaration
		if(symbolTable.getCurrentScopeID()!=1){
			decld_f_var.push_back(make_pair(first+to_string(symbolTable.getCurrentScopeID()),second));  //pushing to the vector to be used during function defination procedure
		}
	}
	var_carrier.clear();
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
};

type_specifier : INT {
	fprintf(logs, "Line %d: type_specifier : INT\n\n", numberOfLines);

	SymbolInfo* s = new SymbolInfo("", "INT");
	type_of_var = "INT";
	$$ = s;
	$$->extraSymbolInfo.stringConcatenator = "int ";
	fprintf(logs, "%s\n\n", $$->extraSymbolInfo.stringConcatenator.c_str());
} | FLOAT {
	fprintf(logs,"Line %d: type_specifier : FLOAT\n\n",numberOfLines);
	SymbolInfo* s = new SymbolInfo("","FLOAT");
	type_of_var = "FLOAT";
	$$ = s;
	$$->extraSymbolInfo.stringConcatenator = "float ";
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | VOID {
	fprintf(logs,"Line %d: type_specifier : VOID\n\n",numberOfLines);
	SymbolInfo* s = new SymbolInfo("","VOID");
	type_of_var = "VOID";
	$$ = s;
	$$->extraSymbolInfo.stringConcatenator = "void ";
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
};

declaration_list : declaration_list COMMA ID {
	if(type_of_var!="VOID"){
		fprintf(logs,"Line %d: declaration_list : declaration_list COMMA ID\n\n",numberOfLines);

		SymbolInfo* test = symbolTable.currentScopeLookUp($3->getName());
		if(test!=0){
			fprintf(errors,"Error at Line %d  : Multiple Declaration of %s\n\n",numberOfLines,$3->getName().c_str());
			numberOfErrors++;
		} else {
			SymbolInfo* obj = new SymbolInfo($3->getName(),$3->getType());
			obj->extraSymbolInfo.typeOfID = "VARIABLE";
			obj->extraSymbolInfo.typeOfVar = type_of_var;
			symbolTable.InsertModified(obj);
		}

		$1->extraSymbolInfo.stringConcatenator.append(getFromSymbolSet("comma"));
		$$->extraSymbolInfo.stringConcatenator.append($3->getName());
		var_carrier.push_back(make_pair($3->getName(),""));
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	}
} | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
	if(type_of_var!="VOID") {
		fprintf(logs,"Line %d: declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n",numberOfLines);
		SymbolInfo* test = symbolTable.currentScopeLookUp($3->getName());

		if(test!=0) {
			fprintf(errors,"Error at Line %d  : Multiple Declaration of %s\n\n",numberOfLines,$3->getName().c_str());
			numberOfErrors++;
		} else {
			SymbolInfo* obj = new SymbolInfo($3->getName(),$3->getType());

			obj->extraSymbolInfo.typeOfID = "ARRAY";
			obj->extraSymbolInfo.typeOfVar = type_of_var;
			obj->extraSymbolInfo.sizeOfArray = $5->getName();
			symbolTable.InsertModified(obj);
		}
		string temp = $3->getName()+getFromSymbolSet("left_third")+$5->getName()+getFromSymbolSet("right_third");
		$1->extraSymbolInfo.stringConcatenator.append(getFromSymbolSet("comma"));
		$$->extraSymbolInfo.stringConcatenator.append(temp);
		var_carrier.push_back(make_pair($3->getName(), $5->getName()));
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	}
} | ID {
	fprintf(logs,"Line %d: declaration_list : ID\n\n",numberOfLines);

	if(type_of_var!="VOID"){
		SymbolInfo* temp = symbolTable.currentScopeLookUp($1->getName());
		if(temp!=0) {
			numberOfErrors++;
			fprintf(errors,"Error at Line %d  : Multiple declration of %s\n\n",numberOfLines,$1->getName().c_str());
		} else{
			SymbolInfo* obj = new SymbolInfo($1->getName(),$1->getType());
			obj->extraSymbolInfo.typeOfID = "VARIABLE";
			obj->extraSymbolInfo.typeOfVar = type_of_var;
			symbolTable.InsertModified(obj);
		}
	} else{
		numberOfErrors++;
		fprintf(errors,"Error at Line %d  : Variable declared void\n\n",numberOfLines);
	}
	$$->extraSymbolInfo.stringConcatenator = $1->getName();
	var_carrier.push_back(make_pair($1->getName(), ""));
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | ID LTHIRD CONST_INT RTHIRD {
	fprintf(logs,"Line %d: declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n",numberOfLines);

	//checking to see if array type is void or not
	if(type_of_var!="VOID")
	{
		SymbolInfo* temp = symbolTable.currentScopeLookUp($1->getName());
		if(temp!=0){
			fprintf(errors,"Error at Line %d  : Multiple declration of %s\n\n",numberOfLines,$1->getName().c_str());
			numberOfErrors++;
		} else{
			SymbolInfo* obj = new SymbolInfo($1->getName(),$1->getType());
			obj->extraSymbolInfo.typeOfID = "ARRAY";
			obj->extraSymbolInfo.typeOfVar = type_of_var;
			obj->extraSymbolInfo.sizeOfArray = $3->getName();
			symbolTable.InsertModified(obj);
		}
	} else {
		fprintf(errors,"Error at Line %d  :  Array %s declared as void\n\n", numberOfLines,$1->getName().c_str());
		numberOfErrors++;
	}
    string temp = getFromSymbolSet("left_third")+$3->getName()+getFromSymbolSet("right_third");
	$$->extraSymbolInfo.stringConcatenator = $1->getName();
	$$->extraSymbolInfo.stringConcatenator.append(temp);
	var_carrier.push_back(make_pair($1->getName(), $3->getName()));
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
};

statements : statement{
	fprintf(logs,"Line %d: statements : statement\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+"\n";
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | statements statement {
	fprintf(logs,"Line %d: statements : statements statement\n\n", numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+($2->extraSymbolInfo.stringConcatenator+"\n");
	statement_solver = $$->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code + $2->extraSymbolInfo.assm_code;
};

statement : var_declaration {
	fprintf(logs,"Line %d: statement : var_declaration\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | expression_statement {
	fprintf(logs,"Line %d: statement : expression_statement\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | compound_statement {
	fprintf(logs,"Line %d: statement : compound_statement\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | FOR LPAREN expression_statement expression_statement expression RPAREN statement {
	fprintf(logs,"Line %d: statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n",numberOfLines);
	string temp = $3->extraSymbolInfo.stringAdder($4->extraSymbolInfo.stringAdder($5->extraSymbolInfo.stringConcatenator));
	$$->extraSymbolInfo.stringConcatenator = "for"+getFromSymbolSet("left_first")+temp+getFromSymbolSet("right_first")+$7->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	//var type of expression_statements and expression
	string a = $3->extraSymbolInfo.typeOfVar;
	string b = $4->extraSymbolInfo.typeOfVar;
	string c = $5->extraSymbolInfo.typeOfVar;

	if((a=="VOID")||(b=="VOID")||(c=="VOID")){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Expression can not be void\n\n",numberOfLines);
	}else{
		/* ******************* */
		/*                     */
		/* 		ICG Code       */
		/*                     */
		/* ******************* */
		char *label1 = newLabel(), *label2 = newLabel();

		string temp_code = $3->extraSymbolInfo.assm_code+string(label1)+":\n"+$4->extraSymbolInfo.assm_code+"\tMOV AX, "+$4->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 0\n"+"\tJE "+string(label2)+"\n"+$7->extraSymbolInfo.assm_code+$5->extraSymbolInfo.assm_code+"\tJMP "+string(label1)+"\n"+string(label2)+":\n\n";
		$$->extraSymbolInfo.assm_code = temp_code;
	}
} | IF LPAREN expression RPAREN statement %prec LOWER_PREC_THAN_ELSE{
	fprintf(logs,"Line %d: IF LPAREN expression RPAREN statement\n\n",numberOfLines);
	string temp = $3->extraSymbolInfo.stringAdder(getFromSymbolSet("right_first"));
	$$->extraSymbolInfo.stringConcatenator = "if"+getFromSymbolSet("left_first")+temp+$5->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	string a = $3->extraSymbolInfo.typeOfVar;
	if(a=="VOID"){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Expression can not be void\n\n",numberOfLines);
	}
	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	char *label1 = newLabel();
	string temp_code = $3->extraSymbolInfo.assm_code+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 0\n"+"\tJE "+string(label1)+"\n"+$5->extraSymbolInfo.assm_code+string(label1)+":\n\n";
	$$->extraSymbolInfo.assm_code = temp_code;

} | IF LPAREN expression RPAREN statement ELSE statement {
		fprintf(logs,"Line %d: IF LPAREN expression RPAREN statement ELSE statement\n\n",numberOfLines);
		string temp = $3->extraSymbolInfo.stringAdder(getFromSymbolSet("right_first"));
		string temp2 = $5->extraSymbolInfo.stringAdder("else"+$7->extraSymbolInfo.stringConcatenator);
		$$->extraSymbolInfo.stringConcatenator = "if"+getFromSymbolSet("left_first")+temp+temp2;
		fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

		string a = $3->extraSymbolInfo.typeOfVar;
		if(a=="VOID"){
			numberOfErrors++;
			fprintf(errors,"Error at Line %d : Expression can not be void\n\n",numberOfLines);
		}else{
			/* ******************* */
			/*                     */
			/* 		ICG Code       */
			/*                     */
			/* ******************* */
			char *label1 = newLabel(), *label2 = newLabel();
			string temp_code = $3->extraSymbolInfo.assm_code+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 0\n"+"\tJE "+string(label1)+"\n"+$5->extraSymbolInfo.assm_code+"\tJMP "+string(label2)+"\n"+"\tJMP "+string(label2)+"\n"+string(label1)+":\n"+$7->extraSymbolInfo.assm_code+string(label2)+":\n\n";

			$$->extraSymbolInfo.assm_code = temp_code;
		}
} | WHILE LPAREN expression RPAREN statement {
	fprintf(logs,"Line %d: WHILE LPAREN expression RPAREN statement\n\n",numberOfLines);
	string temp = $3->extraSymbolInfo.stringAdder(getFromSymbolSet("right_first")+$5->extraSymbolInfo.stringConcatenator);
	$$->extraSymbolInfo.stringConcatenator = "while"+getFromSymbolSet("left_first")+temp;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	string a = $3->extraSymbolInfo.typeOfVar;
	if(a=="VOID"){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Expression can not be void\n\n",numberOfLines);
	}else{
		/* ******************* */
		/*                     */
		/* 		ICG Code       */
		/*                     */
		/* ******************* */
		char *label1 = newLabel(), *label2 = newLabel();

		string temp_code = string(label1)+":\n"+$3->extraSymbolInfo.assm_code+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 0\n"+"\tJE "+string(label2)+"\n"+$5->extraSymbolInfo.assm_code+"\tJMP "+string(label1)+"\n"+string(label2)+":\n\n";
		$$->extraSymbolInfo.assm_code = temp_code;
	}
} | PRINTLN LPAREN ID RPAREN SEMICOLON {
	fprintf(logs,"Line %d: statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = "println"+getFromSymbolSet("left_first")+$3->getName()+getFromSymbolSet("right_first")+getFromSymbolSet("semicolon");
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = "\n\n\tMOV AX, "+$3->getName()+to_string(symbolTable.IDlookUpWithParam($3->getName()))+"\n\tCALL PRINT_INT\n\n";
	$$->extraSymbolInfo.assm_code = temp_code;

} | RETURN expression SEMICOLON {
	fprintf(logs,"Line %d: statement : RETURN expression SEMICOLON\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = "return "+$2->extraSymbolInfo.stringAdder(getFromSymbolSet("semicolon"));
	fprintf(logs,"%s\n\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	string a = $2->extraSymbolInfo.typeOfVar;

	if(a=="VOID"){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Expression can not be void\n\n",numberOfLines);
	}
	return_type_solver = a;

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $2->extraSymbolInfo.assm_code+"\tMOV AX, "+$2->extraSymbolInfo.carr1+"\n"+"\tMOV "+running_f_name+"_return_val"+", AX\n\n"+"\tJMP LABEL_RETURN_"+running_f_name+"\n";
	$$->extraSymbolInfo.assm_code = temp_code;
};

expression_statement : SEMICOLON {
	fprintf(logs,"Line %d: expression_statement : SEMICOLON\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = getFromSymbolSet("semicolon");
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | expression SEMICOLON {
	fprintf(logs,"Line %d: expression_statement : expression SEMICOLON\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringAdder(getFromSymbolSet("semicolon"));
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
};

variable : ID {
	fprintf(logs,"Line %d: variable : ID\n\n",numberOfLines);
	SymbolInfo* temp =  symbolTable.LookUp($1->getName());
	string type="";

	if(temp!=0){
		if(temp->extraSymbolInfo.typeOfID=="ARRAY"){
			numberOfErrors++;
			fprintf(errors,"Error at Line %d : No index on array\n\n",numberOfLines,$1->getName().c_str());
			type = temp->extraSymbolInfo.typeOfVar;
		} else if(temp->extraSymbolInfo.isFunction){
			numberOfErrors++;
			fprintf(errors,"Error at Line %d : Improper Function call\n\n",numberOfLines,$1->getName().c_str());
			type = temp->extraSymbolInfo.returnTypeOfFunction;
		} else{
			type = temp->extraSymbolInfo.typeOfVar;
		}

		$$->extraSymbolInfo.typeOfVar = type;
		$$->extraSymbolInfo.typeOfID = temp->extraSymbolInfo.typeOfID;
		$$->setName(temp->getName());
		$$->setType(temp->getType());
	} else{
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Undeclared variable : %s\n\n",numberOfLines,$1->getName().c_str());
	}
	$$->extraSymbolInfo.stringConcatenator = $1->getName();
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->getName()+
	to_string(symbolTable.IDlookUpWithParam($1->getName()));
	$$->extraSymbolInfo.assm_code = "";
} | ID LTHIRD expression RTHIRD {
	fprintf(logs,"Line %d: variable : ID LTHIRD expression RTHIRD\n\n",numberOfLines);

	// check that id exixts in scope table or not
	SymbolInfo* temp = symbolTable.LookUp($1->getName());

	if(temp!=0){
		string typeOfID = temp->extraSymbolInfo.typeOfID;

		if(typeOfID!="ARRAY"){
			numberOfErrors++;
			fprintf(errors,"Error at Line %d : Index Not on Array\n\n",numberOfLines);
		} else{
			string type = $3->extraSymbolInfo.typeOfVar; //index expression type
			string arr_type = $1->extraSymbolInfo.typeOfVar;
			if(type!="INT"){
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : Non Integer Array Index\n\n",numberOfLines);
			}
		}

		temp->extraSymbolInfo.isFunction ? $$->extraSymbolInfo.typeOfVar = temp->extraSymbolInfo.returnTypeOfFunction :	$$->extraSymbolInfo.typeOfVar = temp->extraSymbolInfo.typeOfVar;

		$$->extraSymbolInfo.typeOfID = temp->extraSymbolInfo.typeOfID;
		$$->setName(temp->getName());
		$$->setType(temp->getType());
		$$->extraSymbolInfo.indexOfArray  = temp->extraSymbolInfo.indexOfArray;
		$$->extraSymbolInfo.sizeOfArray = temp->extraSymbolInfo.sizeOfArray;
	} else {
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Undeclared variable : %s\n\n",numberOfLines,$1->getName().c_str());
	}

	string t = getFromSymbolSet("left_third")+$3->extraSymbolInfo.stringAdder(getFromSymbolSet("right_third"));
	$$->extraSymbolInfo.stringConcatenator = $1->getName()+t;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $3->extraSymbolInfo.assm_code+"\tMOV BX, "+$3->extraSymbolInfo.carr1+"\n\tADD BX, BX\n";
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = $1->getName()+
	to_string(symbolTable.IDlookUpWithParam($1->getName()));
};

expression : logic_expression {
	fprintf(logs,"Line %d: expression : logic expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | variable ASSIGNOP logic_expression {
	fprintf(logs,"Line %d: expression : variable ASSIGNOP logic_expression\n\n",numberOfLines);

	SymbolInfo* s = symbolTable.LookUp($1->getName());

	if(s!=0){
		string v_type = s->extraSymbolInfo.typeOfVar;
		string log_exp_type = $3->extraSymbolInfo.typeOfVar;

		if($3->extraSymbolInfo.typeOfVar=="VOID"){
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : Type Mismatch: cannot assign to VOID type\n\n",numberOfLines);
		} else {
			if(v_type!=log_exp_type)
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : Type Mismatch\n\n",numberOfLines);
			}
			if((v_type=="FLOAT")&&(log_exp_type=="INT")){
				// it's a warning not error
				//numberOfErrors++;
				fprintf(errors,"Warning at Line %d : Integer assigned to Float\n\n",numberOfLines);
			}
			else if((v_type=="INT")&&(log_exp_type=="FLOAT"))
			{
				// it's a warning not error
				//numberOfErrors++;
				fprintf(errors,"Warning at Line %d : Float assigned to Integer\n\n",numberOfLines);
			}
		}
    }

	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;

	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator+getFromSymbolSet("equal")+$3->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */

	string temp_code;
	char* idx_saver = newTemp();
	if($1->extraSymbolInfo.typeOfID == "ARRAY"){
		decld_var_carrier.push_back(make_pair(string(idx_saver), ""));
		temp_code = $1->extraSymbolInfo.assm_code+"\n\tMOV "+string(idx_saver)+", BX\n"+$3->extraSymbolInfo.assm_code+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tMOV BX, "+string(idx_saver)+"\n"+"\tMOV "+$1->extraSymbolInfo.carr1+"[BX], AX\n\n";
		$$->extraSymbolInfo.assm_code = temp_code;
	}else{
		temp_code = $1->extraSymbolInfo.assm_code+$3->extraSymbolInfo.assm_code+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tMOV "+$1->extraSymbolInfo.carr1+", AX\n\n";

		$$->extraSymbolInfo.assm_code = temp_code;
	}
};

logic_expression : rel_expression {
	fprintf(logs,"Line %d: logic_expression : rel_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;

	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | rel_expression LOGICOP rel_expression {
	fprintf(logs,"Line %d: logic_expression : rel_expression LOGICOP rel_expression\n\n",numberOfLines);
	string a_type  = $1->extraSymbolInfo.typeOfVar;
	string b_type  =  $2->extraSymbolInfo.typeOfVar;
	if((a_type=="VOID") || (b_type =="VOID")){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d  : Type Mismatch: cannot operate on VOID type\n\n",numberOfLines);
	}
	string ret_type = "INT";
	$$->extraSymbolInfo.typeOfVar = ret_type;
	string temp = $1->extraSymbolInfo.stringAdder($2->getName()+$3->extraSymbolInfo.stringConcatenator);
	$$->extraSymbolInfo.stringConcatenator = temp;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $1->extraSymbolInfo.assm_code+
					$3->extraSymbolInfo.assm_code;
	char *label1 = newLabel(), *label2 = newLabel(), *label3 = newLabel();
	char *temp_var = newTemp();

	if($2->getName() == "&&"){
		temp_code += "\n\tMOV AX, "+$1->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 1"+"\n\tJNE "+string(label2)+"\n"+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 1"+"\n\tJNE "+string(label2)+"\n"+string(label1)+":\n\tMOV "+string(temp_var)+", 1\n"+"\tJMP "+string(label3)+"\n"+string(label2)+":\n\tMOV "+string(temp_var)+", 0\n"+string(label3)+":\n\n";
	}else if($2->getName()=="||"){
		temp_code += "\n\tMOV AX, "+$1->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 1"+"\n\tJE "+string(label2)+"\n"+"\tMOV AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tCMP AX, 1"+"\n\tJE "+string(label2)+"\n"+string(label1)+":\n\tMOV "+string(temp_var)+", 0\n"+"\tJMP "+string(label3)+"\n"+string(label2)+":\n\tMOV "+string(temp_var)+", 1\n"+string(label3)+":\n\n";
	}
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = string(temp_var);
	decld_var_carrier.push_back(make_pair(string(temp_var), ""));
};

rel_expression	: simple_expression {
	fprintf(logs,"Line %d: rel_expression : simple_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;

	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | simple_expression RELOP simple_expression {
	fprintf(logs,"Line %d: rel_expression : simple_expression RELOP simple_expression\n\n",numberOfLines);

	string a_type  = $1->extraSymbolInfo.typeOfVar;
	string b_type  =  $2->extraSymbolInfo.typeOfVar;
	if((a_type=="VOID") || (b_type =="VOID")){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d  : Type Mismatch: cannot operate on VOID type\n\n",numberOfLines);
	}

	string ret_type = "INT";
	$$->extraSymbolInfo.typeOfVar = ret_type;
	string temp = $1->extraSymbolInfo.stringAdder($2->getName()+$3->extraSymbolInfo.stringConcatenator);
	$$->extraSymbolInfo.stringConcatenator = temp;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $1->extraSymbolInfo.assm_code+$3->extraSymbolInfo.assm_code+"\tMOV AX, "+$1->extraSymbolInfo.carr1+"\n"+"\tCMP AX, "+$3->extraSymbolInfo.carr1+"\n";
	char* temp_var = newTemp();
	char *label1=newLabel(), *label2=newLabel();

	if($2->getName() == "<"){
		temp_code += "\tJL "+string(label1)+"\n";
	}else if($2->getName() == "<="){
		temp_code += "\tJLE "+string(label1)+"\n";
	}else if($2->getName() == ">"){
		temp_code += "\tJG "+string(label1)+"\n";
	}else if($2->getName() == ">="){
		temp_code += "\tJGE "+string(label1)+"\n";
	}else if($2->getName()== "=="){
		temp_code += "\tJE "+string(label1)+"\n";
	}else{
		temp_code += "\tJNE "+string(label1)+"\n";
	}
	temp_code += "\tMOV "+string(temp_var)+", 0\n"+"\tJMP "+string(label2)+"\n"+string(label1)+":\n\tMOV "+string(temp_var)+", 1\n"+string(label2)+":\n\n";
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = string(temp_var);
	decld_var_carrier.push_back(make_pair(string(temp_var), ""));

};

simple_expression : term {
	fprintf(logs,"Line %d: simple_expression : term\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | simple_expression ADDOP term {
	fprintf(logs,"Line %d: simple_expression : simple_expression ADDOP term\n\n",numberOfLines);

	string a_type = $1->extraSymbolInfo.typeOfVar;
	string b_type = $3->extraSymbolInfo.typeOfVar;
	string ret_type  = "";

	//type checking for operands to be added and type conversion
	if((a_type=="VOID")||(b_type=="VOID"))
	{
		numberOfErrors++;
		fprintf(errors,"Error at Line %d  : Add operation with void\n\n",numberOfLines);
		ret_type = "INT";
	} else if((a_type=="FLOAT")||(b_type=="FLOAT")){
		if(((a_type=="FLOAT")&&(b_type=="INT"))||((a_type=="INT")&&(b_type=="FLOAT")))
			fprintf(errors,"Warning at Line %d  : Integer converted to float during Addition.\n\n",numberOfLines);
			ret_type = "FLOAT";
	} else if((a_type=="INT")&&(b_type=="INT")){
			ret_type = "INT";
	}

	SymbolInfo* s = new SymbolInfo("",ret_type);
	$$ = s;
	$$->extraSymbolInfo.typeOfVar = ret_type;
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringAdder($2->getName().append($3->extraSymbolInfo.stringConcatenator));
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = "\n"+$1->extraSymbolInfo.assm_code+$3->extraSymbolInfo.assm_code+"\n\tMOV AX, "+$1->extraSymbolInfo.carr1+"\n";
	char* temp_var = newTemp();

	if($2->getName() == "+"){
		temp_code += "\tADD AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tMOV "+string(temp_var)+", AX\n\n";
	}else if($2->getName() == "-"){
		temp_code += "\tSUB AX, "+$3->extraSymbolInfo.carr1+"\n"+"\tMOV "+string(temp_var)+", AX\n\n";
	}
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = string(temp_var);
	decld_var_carrier.push_back(make_pair(string(temp_var), ""));
};

term :	unary_expression {
	fprintf(logs,"Line %d: term : unary_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
} | term MULOP unary_expression {
	fprintf(logs,"Line %d: term : term MULOP unary_expression\n\n",numberOfLines);

	string term_type = $1->extraSymbolInfo.typeOfVar;
	string unary_type = $3->extraSymbolInfo.typeOfVar;
	string mult_operator = $2->getName();
	string ret_type = "";

	map<string,int>command_map;
	command_map["*"] = 1;
	command_map["/"] = 2;
	command_map["%"] = 3;

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	char* temp_var = newTemp();
	string res = string(temp_var);
	string temp_code = $1->extraSymbolInfo.assm_code+$3->extraSymbolInfo.assm_code;

	switch(command_map[mult_operator])
	{
		case 1:
			{
				if((term_type=="VOID")||(unary_type=="VOID")){
					numberOfErrors++;
					fprintf(errors,"Error at Line %d : Multiplication operation with void\n\n",numberOfLines);
					ret_type = "INT";
				} else if((term_type=="FLOAT")||(unary_type=="FLOAT")){
					if(((term_type=="FLOAT")&&(unary_type=="INT"))||((term_type=="INT")&&(unary_type=="FLOAT")))
						fprintf(errors,"Warning at Line %d : Integer converted to float during Multiplication.\n\n",numberOfLines);
					ret_type = "FLOAT";
				} else if((term_type=="INT")&&(term_type=="INT")){
					ret_type = "INT";
				}
				SymbolInfo* s = new SymbolInfo("",ret_type);
				$$ = s;
				$$->extraSymbolInfo.typeOfVar = ret_type;
				$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringAdder($2->getName().append($3->extraSymbolInfo.stringConcatenator));
				fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

				/* ******************* */
				/*                     */
				/* 		ICG Code       */
				/*                     */
				/* ******************* */
				temp_code += "\n\tMOV AX, " + $1->extraSymbolInfo.carr1 + "\n" + "\tMOV BX, " + $3->extraSymbolInfo.carr1 + "\n" + "\tMUL BX\n" + "\tMOV " + res + ", AX\n\n";
				$$->extraSymbolInfo.assm_code = temp_code;
				$$->extraSymbolInfo.carr1 = res;
				decld_var_carrier.push_back(make_pair(res, ""));
			}
			break;
		case 2:{
				if((term_type=="VOID")||(unary_type=="VOID")){
					numberOfErrors++;
					fprintf(errors,"Error at Line %d : Division operation with void\n\n",numberOfLines);
					ret_type = "INT";
				}else if((term_type=="FLOAT")||(unary_type=="FLOAT")){
					if(((term_type=="FLOAT")&&(unary_type=="INT"))||((term_type=="INT")&&(unary_type=="FLOAT")))
						fprintf(errors,"Warning at Line %d : Integer converted to float during Division.\n\n",numberOfLines);
					ret_type = "FLOAT";
				}else if((term_type=="INT")&&(term_type=="INT"))
				{
					ret_type = "INT";
				}
				SymbolInfo* s = new SymbolInfo("",ret_type);
				$$ = s;
				$$->extraSymbolInfo.typeOfVar = ret_type;
				$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringAdder($2->getName().append($3->extraSymbolInfo.stringConcatenator));
				fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

				/* ******************* */
				/*                     */
				/* 		ICG Code       */
				/*                     */
				/* ******************* */
				temp_code += "\n\tXOR DX, DX";
				temp_code += "\n\tMOV AX, " +$1->extraSymbolInfo.carr1+"\n"+"\tMOV BX, "+$3->extraSymbolInfo.carr1 +"\n"+"\tDIV BX\n"+"\tMOV "+res+", AX\n\n";
				$$->extraSymbolInfo.assm_code = temp_code;
				$$->extraSymbolInfo.carr1 = res;
				decld_var_carrier.push_back(make_pair(res, ""));
			}
			break;
		case 3:{
				if((term_type=="VOID")||(unary_type=="VOID")){
					numberOfErrors++;
					fprintf(errors,"Error at Line %d : Integer operand not on modulus operator\n\n",numberOfLines);
					ret_type = "INT";
				} else if((term_type!="INT")||(unary_type!="INT")){
					numberOfErrors++;
					fprintf(errors,"Error at Line %d : Integer operand not on modulus operator\n\n",numberOfLines);
					ret_type = "INT";
				}else if((term_type=="INT")&&(term_type=="INT"))
				{
					ret_type = "INT";
				}
				SymbolInfo* s = new SymbolInfo("",ret_type);
				$$ = s;
				$$->extraSymbolInfo.typeOfVar = ret_type;
				$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringAdder($2->getName().append($3->extraSymbolInfo.stringConcatenator));
				fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

				/* ******************* */
				/*                     */
				/* 		ICG Code       */
				/*                     */
				/* ******************* */
				temp_code += "\tXOR DX, DX\n";
				temp_code += "\tMOV AX, " + $1->extraSymbolInfo.carr1 + "\n" + "\tMOV BX, " + $3->extraSymbolInfo.carr1 + "\n" + "\tDIV BX\n" + "\tMOV " + res + ", DX\n\n";
				$$->extraSymbolInfo.assm_code = temp_code;
				$$->extraSymbolInfo.carr1 = res;
				decld_var_carrier.push_back(make_pair(res, ""));
			}
			break;
	}
};

unary_expression : ADDOP unary_expression {
	fprintf(logs,"Line %d: unary_expression : ADDOP unary_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->getName().append($2->extraSymbolInfo.stringConcatenator);
	$$->extraSymbolInfo.typeOfVar = $2->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	// VOID check
	if($2->extraSymbolInfo.stringConcatenator=="VOID"){
		fprintf(errors,"Error at Line %d : Unary expression cannot be void\n\n",numberOfLines);
		numberOfErrors++;
	}else{
		string temp_code = $2->extraSymbolInfo.assm_code;

		if($1->getName() == "-"){
			temp_code += "\tMOV AX, "+$2->extraSymbolInfo.carr1+"\n"+"\tNEG AX\n"+"\tMOV "+$2->extraSymbolInfo.carr1+", AX\n\n";
			$$->extraSymbolInfo.assm_code = temp_code;
			$$->extraSymbolInfo.carr1 = $2->extraSymbolInfo.carr1;	

		}
	}
} | NOT unary_expression {
	fprintf(logs,"Line %d: unary_expression : NOT unary_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->getName().append($2->extraSymbolInfo.stringConcatenator);
	$$->extraSymbolInfo.typeOfVar = "INT";
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
	// VOID check
	if($2->extraSymbolInfo.stringConcatenator=="VOID")
	{
		fprintf(errors,"Error at Line %d : Unary expression cannot be void\n\n",numberOfLines);
		numberOfErrors++;
	}else{
		char* temp_var = newTemp();
		string temp_code = $2->extraSymbolInfo.assm_code;
		temp_code += "\tMOV AX, "+$2->extraSymbolInfo.carr1+"\n"+"\tNOT AX\n"+"\tMOV "+string(temp_var)+", AX\n\n";
		$$->extraSymbolInfo.assm_code = temp_code;
		$$->extraSymbolInfo.carr1 = string(temp_var);
		decld_var_carrier.push_back(make_pair(string(temp_var), ""));
	}
} | factor {
	fprintf(logs,"Line %d: unary_expression : factor\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	// at this point don't need t print variable type
	// fprintf(logs,"%s\n\n",$$->extraSymbolInfo.typeOfVar.c_str());
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
};

factor	: variable {
	fprintf(logs,"Line %d: factor : variable\n\n", numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $1->extraSymbolInfo.assm_code;

	if($1->extraSymbolInfo.typeOfID == "ARRAY"){
		char* temp_var = newTemp();
		temp_code += "\tMOV AX, "+$1->extraSymbolInfo.carr1+"[BX]\n"+"\tMOV "+string(temp_var)+", AX\n";
		decld_var_carrier.push_back(make_pair(string(temp_var), ""));
		$$->extraSymbolInfo.carr1 = string(temp_var);	
	}else{
		$$->extraSymbolInfo.carr1 = $1->extraSymbolInfo.carr1;
	}
	$$->extraSymbolInfo.assm_code = temp_code;
} | ID LPAREN argument_list RPAREN {
	fprintf(logs,"Line %d: factor : ID LPAREN argument_list RPAREN\n\n",numberOfLines);

	$$->extraSymbolInfo.stringConcatenator = $1->getName()+getFromSymbolSet("left_first")+$3->extraSymbolInfo.stringConcatenator+getFromSymbolSet("right_first");
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	SymbolInfo* s = symbolTable.LookUp($1->getName());

	if(s==0){
		numberOfErrors++;
		fprintf(errors,"Error at Line %d : Undefined or Undeclared function\n\n",numberOfLines);
		$3->extraSymbolInfo.functionParamList.clear();
	} else {
		if(s->extraSymbolInfo.typeOfID=="FUNCTION"){
			if(s->extraSymbolInfo.isFunction)
			{
				//check the num of arguments matches or not
				int given_arg_list = $3->extraSymbolInfo.functionParamList.size();
				int defined_arg_list = s->extraSymbolInfo.functionParamList.size();

				if(given_arg_list!=defined_arg_list){
					numberOfErrors++;
					fprintf(errors,"Error at Line %d : Unequal Number of function arguments\n\n",numberOfLines);
					$3->extraSymbolInfo.functionParamList.clear();
				}else{
					//Finally check for argument sequence of defined and called function
					for(int i=0;i<defined_arg_list;i++)
					{
						string temp1 = $3->extraSymbolInfo.functionParamList[i].second;
						string temp2 = s->extraSymbolInfo.functionParamList[i].second;

						if(temp1!=temp2)
						{
							numberOfErrors++;
							fprintf(errors,"Error at Line %d : Argument Type Mismatch with function defination \n\n",numberOfLines);
							break;
						}
					}
					$3->extraSymbolInfo.functionParamList.clear();
				}

				$$->extraSymbolInfo.typeOfVar = s->extraSymbolInfo.returnTypeOfFunction;
				$$->extraSymbolInfo.typeOfID = s->extraSymbolInfo.typeOfID;
			} else {
				numberOfErrors++;
				fprintf(errors,"Error at Line %d :function not properly defined or declared \n\n",numberOfLines);
				$$->extraSymbolInfo.typeOfVar = s->extraSymbolInfo.returnTypeOfFunction;
				$$->extraSymbolInfo.typeOfID = s->extraSymbolInfo.typeOfID;
			}
		} else{
			numberOfErrors++;
			fprintf(errors,"Error at Line %d : Function call on Non function ID\n\n",numberOfLines);
			$$->extraSymbolInfo.typeOfVar = "INT";
			arg_param_list.clear();
		}

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	string temp_code = $3->extraSymbolInfo.assm_code;

	for(int i=0;i<s->extraSymbolInfo.modfd_param_list.size();i++){
		temp_code += "\tMOV AX, "+$3->extraSymbolInfo.var_declared_list[i].first+"\n"+"\tMOV "+s->extraSymbolInfo.modfd_param_list[i]+", AX\n";
	}

	temp_code += "\tCALL "+$1->getName()+"\n"+"\tMOV AX, "+$1->getName()+"_return_val"+"\n";

	char* temp_var = newTemp();
	string result = string(temp_var);
	temp_code += "\tMOV "+result+", AX\n";
	
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = result;
	decld_var_carrier.push_back(make_pair(result, ""));
	}
} | LPAREN expression RPAREN {
	fprintf(logs,"Line %d: factor : LPAREN expression RPAREN\n\n",numberOfLines);
	SymbolInfo* s = new SymbolInfo();

	string temp = getFromSymbolSet("left_first")+$2->extraSymbolInfo.stringAdder(getFromSymbolSet("right_first"));
	s->extraSymbolInfo.stringConcatenator = temp;
	s->extraSymbolInfo.typeOfVar = $2->extraSymbolInfo.typeOfVar;
	$$=s;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.assm_code = $2->extraSymbolInfo.assm_code;
	$$->extraSymbolInfo.carr1 = $2->extraSymbolInfo.carr1;
} | CONST_INT {
	fprintf(logs,"Line %d: factor : CONST_INT\n\n",numberOfLines);
	$1->extraSymbolInfo.typeOfVar = "INT";
	$1->extraSymbolInfo.typeOfID = "CONST_INT";
	$$->extraSymbolInfo.stringConcatenator = $1->getName();
	$$->extraSymbolInfo.indexOfArray = $1->getName();
	$$->extraSymbolInfo.typeOfID = $1->extraSymbolInfo.typeOfID;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->getName();

} | CONST_FLOAT {
	$1->extraSymbolInfo.typeOfVar = "FLOAT";
	$1->extraSymbolInfo.typeOfID = "CONST_FLOAT";
	fprintf(logs,"Line %d: factor : CONST_FLOAT\n\n",numberOfLines);
	$$->extraSymbolInfo.stringConcatenator = $1->getName();
	$$->extraSymbolInfo.indexOfArray = $1->getName();
	$$->extraSymbolInfo.typeOfID = $1->extraSymbolInfo.typeOfID;
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$->extraSymbolInfo.carr1 = $1->getName();

} | variable INCOP {
	fprintf(logs,"Line %d: factor : variable INCOP\n\n",numberOfLines);
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	$$->extraSymbolInfo.stringConcatenator = $1->getName()+$2->getName();
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		IGC Code       */
	/*                     */
	/* ******************* */
	char* temp_var = newTemp();
	string temp_code = $1->extraSymbolInfo.assm_code;
	if($1->extraSymbolInfo.typeOfID=="ARRAY"){
		temp_code += "\tMOV AX,"+$1->extraSymbolInfo.carr1+"[BX]\n"+"\tMOV "+string(temp_var)+",AX\n"+"\tINC AX\n"+"\tMOV "+$1->extraSymbolInfo.carr1+"[BX],AX\n\n";
	}else{
		temp_code += "\tMOV AX,"+$1->extraSymbolInfo.carr1+"\n"+"\tMOV "+string(temp_var)+",AX\n"+"\tINC AX\n"+"\tMOV "+$1->extraSymbolInfo.carr1+",AX\n\n";
	}
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = string(temp_var);
	decld_var_carrier.push_back(make_pair(string(temp_var), ""));
} | variable DECOP {
	fprintf(logs,"Line %d: factor : variable DECOP\n\n",numberOfLines);
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.typeOfVar;
	$$->extraSymbolInfo.stringConcatenator = $1->getName()+$2->getName();
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	char* temp_var = newTemp();
	string temp_code = $1->extraSymbolInfo.assm_code;
	if($1->extraSymbolInfo.typeOfID=="ARRAY"){
		temp_code += "\tMOV AX,"+$1->extraSymbolInfo.carr1+"[BX]\n"+"\tMOV "+string(temp_var)+",AX\n"+"\tDEC AX\n"+"\tMOV "+$1->extraSymbolInfo.carr1+"[BX],AX\n\n";
	}else{
		temp_code += "\tMOV AX,"+$1->extraSymbolInfo.carr1+"\n"+"\tMOV "+string(temp_var)+",AX\n"+"\tDEC AX\n"+"\tMOV "+$1->extraSymbolInfo.carr1+",AX\n\n";
	}
	$$->extraSymbolInfo.assm_code = temp_code;
	$$->extraSymbolInfo.carr1 = string(temp_var);
	decld_var_carrier.push_back(make_pair(string(temp_var), ""));
};

argument_list : arguments{
	fprintf(logs,"Line %d: argument_list : arguments\n\n",numberOfLines);

	//so we can get variable name and type Here
	SymbolInfo* s = new SymbolInfo();
	s->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	for(int i=0;i<$1->extraSymbolInfo.functionParamList.size();i++)
	{
		s->extraSymbolInfo.functionParamList.push_back(make_pair($1->extraSymbolInfo.functionParamList[i].first,$1->extraSymbolInfo.functionParamList[i].second));
		s->extraSymbolInfo.var_declared_list.push_back(make_pair($1->extraSymbolInfo.var_declared_list[i].first, ""));
	}

	/* ******************* */
	/*                     */
	/* 		IGC Code       */
	/*                     */
	/* ******************* */

	s->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
	$$ = s;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());
} | {
	SymbolInfo* s = new SymbolInfo("","");
	$$=s;
};

arguments : arguments COMMA logic_expression {
	fprintf(logs,"Line %d: arguments : arguments COMMA logic_expression\n\n",numberOfLines);
	$$->extraSymbolInfo.typeOfVar = $1->extraSymbolInfo.stringConcatenator.append(getFromSymbolSet("comma")+$3->extraSymbolInfo.stringConcatenator);

	string name = $3->getName();
	string variable_type = $3->extraSymbolInfo.typeOfVar;

	if($3->extraSymbolInfo.typeOfVar == "VOID")
	{
		numberOfErrors++;
		fprintf(logs,"Line %d: Void passed as parameter\n\n",numberOfLines);
	}else{
		$$->extraSymbolInfo.functionParamList.push_back(make_pair(name,variable_type));
	}

	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */
	$$ -> extraSymbolInfo.var_declared_list.push_back(make_pair($3->extraSymbolInfo.carr1, ""));
	$$ -> extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code + $3->extraSymbolInfo.assm_code;
} | logic_expression{
	fprintf(logs,"Line %d: arguments : logic_expression\n\n",numberOfLines);

	string name = $1->getName();
	string variable_type = $1->extraSymbolInfo.typeOfVar;

	if($1->extraSymbolInfo.typeOfVar == "VOID")
	{
		numberOfErrors++;
		fprintf(logs,"Line %d: Void passed as parameter\n\n",numberOfLines);
	}else{
		$$->extraSymbolInfo.functionParamList.push_back(make_pair(name,variable_type));
	}

	$$->extraSymbolInfo.stringConcatenator = $1->extraSymbolInfo.stringConcatenator;
	fprintf(logs,"%s\n\n",$$->extraSymbolInfo.stringConcatenator.c_str());

	/* ******************* */
	/*                     */
	/* 		ICG Code       */
	/*                     */
	/* ******************* */

	$$ -> extraSymbolInfo.var_declared_list.push_back(make_pair($1->extraSymbolInfo.carr1, ""));
	$$->extraSymbolInfo.assm_code = $1->extraSymbolInfo.assm_code;
};
%%

int main(int argc,char *argv[])
{

	FILE* fp;

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logs = fopen("log.txt","w");
	errors = fopen("error.txt","w");

	symbolSet();
	yyin=fp;
	yyparse();

    fprintf(logs,"Total lines: %d\n",numberOfLines-1);
	fprintf(logs,"Total errors: %d\n\n",numberOfErrors);
    fprintf(errors,"Total errors: %d\n\n",numberOfErrors);

	fclose(yyin);
    fclose(errors);
	fclose(logs);

	return 0;
}