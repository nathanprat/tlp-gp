// Generated by Bisonc++ V4.08.00 on Sat, 15 Mar 2014 16:42:51 +0100

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
// $insert scanner.h
#include "../scanner/Scanner.h"
// $insert preincludes
#include "../headers.h"


#undef Parser
class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
	int parse();
	
	void init() {
		m_data = new Data();
	}
	
	void setData(Parser * parser) {
		m_data = parser->getData();
	}
	
	Data * getData() {
		return m_data;
	}

	void addDomain(std::string * name) {
		m_data->addDomain(name);
	}
	
	bool isDomain(std::string * name) {
		return m_data->isDomain(name);
	}

	bool addRequirement(int req) {
		return m_data->addRequirement(req);
	}

	bool isRequirement(int req) {
		return m_data->isRequirement(req);
	}
	
	bool addTypes(std::vector<TypedList*> * typedList_list) {
		return m_data->addTypes(typedList_list);
	}
	
	bool addConstants(std::vector<TypedList*> * typedList_list) {
		return m_data->addConstants(typedList_list);
	}
	
	bool addPredicate(std::string * name, std::vector<TypedList*> * typedList_list) {
		return m_data->addPredicate(name, typedList_list);
	}
	
	bool addFunctions(std::vector< std::pair< std::string*, std::vector<TypedList*>* >* > * function_skeleton_list, std::vector<std::string> * return_type) {
		return m_data->addFunctions(function_skeleton_list, return_type);
	}
	
	bool addDurativeAction(std::string * name, std::vector<TypedList*> * typedList_list, float number, std::vector< std::pair< std::pair< std::vector< std::string > *, std::string *> * , int >* > * timed_GD, std::vector< std::pair< std::pair< std::vector< std::string > *, std::string *> * , int >* > * cond_effect) {
		return m_data->addDurativeAction(name, typedList_list, number, timed_GD, cond_effect);
	}
	
	void addProblem(std::string * name) {
		m_data->addProblem(name);
	}
	
	bool addObjects(std::vector<TypedList*> * typedList_list) {
		return m_data->addObjects(typedList_list);
	}
	
	bool addInit(std::pair< std::pair< std::vector< std::string > *, std::string *> *, bool > * literal, float at) {
		return m_data->addInit(literal, at);
	}
	
	bool addGoals(std::vector< std::vector< std::pair< std::pair< std::vector< std::string > *, std::string *> * , int >* > * > * pre_GD) {
		return m_data->addGoals(pre_GD);
	}
		
	void display() {
		m_data->display();
	}

	void lexical_error(std::string msg) {
		m_data->lexical_error(msg);
	}
	
	
    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
        void exceptionHandler__(std::exception const &exc);

    // our stuff:
        Data * m_data;
};


#endif
