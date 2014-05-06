/*
 * tlpgp1.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: nathan
 */

#include "tlpgp1.h"

Tlpgp1::Tlpgp1() {
	// TODO Auto-generated constructor stub
	m_domainptr = nullptr;
	m_problemptr = nullptr;
}

Tlpgp1::Tlpgp1(Domain *domain, Problem *problem):m_domainptr(domain), m_problemptr(problem){}

Tlpgp1::~Tlpgp1() {
	// TODO Auto-generated destructor stub
}


void Tlpgp1::generateGraph() {
	vector<pair<Fluent*, Attribute> > *inits, *goals ;
	vector<DurativeAction*> *actions ;
	pair< vector<DurativeAction*>, vector<pair<Attribute, Fluent*>> > level0,level1,level2,level3;
	DurativeAction goalsAction("Goals") ;
	Sat sol;

	vector< Fluent *> vect ;
	vector<pair<Attribute, Fluent*> > vect2,vect3,inits2 ;
	Fluent *f;
	Attribute a;
	pair<Attribute, Fluent*> p;

	cout << m_domainptr->getName() <<endl;
	//data->display() ;

	inits = m_problemptr->getInits();
	goals = m_problemptr->getGoals();
	actions = m_domainptr->getActions();
	//actions = data->getDomain()->getActions();

	/*
	for(auto it = goals->begin(); it != goals->end(); ++it){
		f = (*it).first;
		a = (*it).second;
		goalsAction.addCondition(a,f);
	}
	cout << "GOALS: " << goalsAction.getPreconditions().size() << endl;


	// inits2 = inits inverted
	for(auto it = inits->begin(); it != inits->end(); ++it){
		f = (*it).first;
		a = (*it).second;
		p.first = a;
		p.second = f;
		inits2.push_back(p);
	}

	cout << "(generateGraph) Inits : " << inits->size() << endl;
	for(auto it = inits->begin(); it != inits->end(); ++it) //error with the first element
		cout << "\t" << (*it).first->to_string() << endl;

	cout << "(generateGraph) Goals : " << goals->size() << endl;
	for(auto it = goals->begin(); it != goals->end(); ++it) //error with the first element
		cout << "\t" << (*it).first->to_string() << endl;

	cout << "(generateGraph) Actions : " << actions->size()<< endl;
	for(auto it_act = actions->begin(); it_act != actions->end(); ++it_act) {//error with the first element
		cout << "\n" <<(*it_act)->getName() << endl;

		vect = (*it_act)->getPreconditions();
		cout << "(generateGraph) preconditions size:" << vect.size() << endl;
		for(auto it = vect.begin(); it != vect.end();++it){
			if(vect.size() != 0)
				cout << (*it)->to_string() <<endl;
			//cout << "plop" <<endl;
		}

		vect2 = (*it_act)->getEffects();
		cout << "(generateGraph) effects size:" << vect2.size() << endl;
		for(auto it = vect2.begin(); it != vect2.end(); ++it){
			if(vect2.size() != 0)
				cout << (*it).second->to_string() <<endl;
			//cout << "plop" <<endl;
		}

		vect2 = (*it_act)->getNotEffects();
		cout << "(generateGraph) not_effects size:" << vect2.size() << endl;
		for(auto it= vect2.begin(); it != vect2.end(); ++it){
			if(vect2.size() != 0)
				cout << it->second->to_string() <<endl;
			//cout << "plop" <<endl;
		}
	}

	vect2.clear();
	//vect2.insert(vect2.end(),inits2.begin(),inits2.end());
	//vect2 = inits2;
	cout << "\nETAPE 1: " << vect2.size() << endl;
	for(auto it_act = actions->begin(); it_act != actions->end(); ++it_act) {
		if(actionUsable(*it_act, &inits2)){
			cout << (*it_act)->getName() << endl;

			vect3 = (*it_act)->getEffects();
			vect2.insert(vect2.end(), vect3.begin(), vect3.end());
		}
	}
	cout << "RESULT: " << vect2.size() << " " << actionUsable(&goalsAction, &vect2)<< endl;


	cout << "level 0: " << " " << actionUsable(&goalsAction, &vect2)<< endl;

	level1 = nextLevel(actions,vect2);
	cout << "level 1: " << " " << actionUsable(&goalsAction, &vect2)<< endl;
	cout << ": " << level1.first.size() << " " << level1.second.size()<< endl;

	level2 = nextLevel(&level1.first,level1.second);
	cout << "level 2: " << " " << actionUsable(&goalsAction, &vect2)<< endl;
	cout << ": " << level2.first.size() << " " << level2.second.size()<< endl;

	level3 = nextLevel(&level2.first,level2.second);
	cout << "level 2: " << " " << actionUsable(&goalsAction, &vect2)<< endl;
	cout << ": " << level3.first.size() << " " << level3.second.size()<< endl;


	cout << "\nETAPE 2: " << vect2.size() << endl;
	for(auto it_act = actions->begin(); it_act != actions->end(); ++it_act) {
		if(actionUsable(*it_act, &vect2)){
			cout << (*it_act)->getName() << endl;

			vect3 = (*it_act)->getEffects();
			vect2.insert(vect2.end(), vect3.begin(), vect3.end());
		}
	}
	cout << "RESULT: " << vect2.size() << " " << actionUsable(&goalsAction, &inits2)<< endl;

	cout << "\nETAPE 3: " << vect2.size() << endl;
	for(auto it_act = actions->begin(); it_act != actions->end(); ++it_act) {
		if(actionUsable(*it_act, &vect2)){
			cout << (*it_act)->getName() << endl;

			vect3 = (*it_act)->getEffects();
			vect2.insert(vect2.end(), vect3.begin(), vect3.end());
		}
	}
	cout << "RESULT: " << vect2.size() << " " << actionUsable(&goalsAction, &inits2)<< endl;

	*/
	cout << "\n(generateGraph): END OF PRINT" <<endl;

	constraint c (1,2,"<",(*actions)[0],(*actions)[1]);
	c.print();

	sol.initialize();
	sol.solve();

	cout << "\n(generateGraph): END" <<endl;
}

pair< vector<DurativeAction*>, vector<pair<Attribute, Fluent*>> > Tlpgp1::nextLevel(vector<DurativeAction*> *actions,vector<pair<Attribute, Fluent*> > conditions){
	vector<pair<Attribute, Fluent*> > newEffects,tempEffects;
	vector<DurativeAction*> newActions ;
	vector<pair<Attribute, Fluent*> >::iterator pos ;
	pair< vector<DurativeAction*>, vector<pair<Attribute, Fluent*>> > result;

	cout << "\nETAPE : " << conditions.size() << endl;
	for(auto it_act = actions->begin(); it_act != actions->end(); ++it_act) {
		if(actionUsable(*it_act, &conditions)){
			//cout << (*it_act)->getName() << endl;
			newActions.push_back(*it_act);
			tempEffects = (*it_act)->getEffects() ;

			for(auto it_eff = tempEffects.begin(); it_eff != tempEffects.end(); ++it_eff){
				//pos = find(newEffects.begin(), newEffects.end(), it_eff) ;
				if(pos == newEffects.end() ){
					newEffects.push_back(*it_eff);
				}
			}
			newEffects.insert(newEffects.end(),tempEffects.begin(),tempEffects.end());
		}
	}

	result.first = newActions;
	result.second = newEffects;

	return result;
}

// Given a list of fluents, return if the action is activable (ie all preconditions are satisfied)
bool Tlpgp1::actionUsable(DurativeAction* action, vector<pair<Attribute, Fluent*> > *fluents){
	bool res=true ,res2 = true;
	vector< Fluent *> preconditions ;
	Fluent *fluent;

	preconditions = action->getPreconditions();

	//cout << "\n" << "(actionUsable)"<< action->getName();
	//cout << preconditions.size() <<" "<< fluents->size() <<endl;

	for(auto it_precond = preconditions.begin(); it_precond != preconditions.end(); ++it_precond){
		//cout << "preconditons: " << (*it_precond)->to_string() <<endl;
		res2 = false;
		for(auto it_fluents = fluents->begin(); it_fluents != fluents->end(); ++it_fluents){
			fluent = (*it_fluents).second ;
			res2 = res2 || fluent->getPredicate()->getName()==(*it_precond)->getPredicate()->getName() ;
			//cout << res2 <<endl;
			//cout << fluent->getPredicate()->getName() << " " << res2 << endl;
			//cout << "\t" << (*it_var).first->to_string() <<endl;
		}
		//cout << "res: " << res << " res2: " <<res2 <<endl;
		res = (res && res2) ;;
	}

	//cout << " -> " << res ;;

	return res;
}
