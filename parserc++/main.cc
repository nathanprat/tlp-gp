#include "parser/Parser.h"

using namespace std;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
	
    Parser parser_domain;
	FILE *domain, *problem;
	Data *data(0) ;
	//data = new Data();
	vector<pair<Fluent*, Attribute> > inits ;
	vector<DurativeAction*> actions ;
	
	if (argc != 3) {
		cerr << "Usage :\n\t" << argv[0] << " domainFile.pddl problemFile.pddl" << endl;
		exit(1);
	}
	
	if ((domain = fopen(argv[1], "r")) == NULL) {
		cerr << argv[1] << " cannot be opened." << endl;
		exit(2);
	}
	
	if ((problem = fopen(argv[2], "r")) == NULL) {
		cerr << argv[2] << " cannot be opened." << endl;
		exit(3);
	}
	
	dup2(fileno(domain), STDIN_FILENO);
	
	if (fclose(domain) != 0) {
		cerr << argv[1] << " cannot be closed." << endl;
		exit(4);
	}
	
	parser_domain.init();
	if (parser_domain.parse() == 0) {
		cout << "The domain was successfully parsed" << endl;
		Parser parser_problem;
		
		parser_problem.setData(&parser_domain);
		dup2(fileno(problem), STDIN_FILENO);
		
		if (fclose(problem) != 0) {
			cerr << argv[2] << " cannot be closed." << endl;
			exit(5);
		}
		
		if (parser_problem.parse() == 0) {
			cout << "The problem was successfully parsed" << endl;
			parser_problem.display();
			cout << data <<endl;
			data = parser_problem.getData();
			//inits = parser_problem.getData()->getInits();
			cout << data <<endl;
		}
	}
	else {
		if (fclose(problem) != 0) {
			cerr << argv[2] << " cannot be closed." << endl;
			exit(5);
		}
	}

	cout << data->getDomain()->getName() <<endl;
	//data->display() ;

	inits = data->getInits() ;
	actions = data->getActions();
	//actions = data->getDomain()->getActions();

	cout << "(test) Inits : " << inits.size() << endl;
	for(vector<pair<Fluent*, Attribute> >::iterator it = inits.begin()+1; it != inits.end(); ++it) //error with the first element
		cout << "\t" << (*it).first->to_string() << endl;

	cout << "(test) Actions :" << endl;
	for(vector<DurativeAction*>::iterator it = actions.begin()+1; it != actions.end(); ++it) //error with the first element
		cout << "\t" << (*it)->to_string() << endl;

	return 0;
}
