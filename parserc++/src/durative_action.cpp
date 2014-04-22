#include "durative_action.h"
#include <iostream>

DurativeAction::DurativeAction(string name):m_name(name) {}

DurativeAction::~DurativeAction() {}

string DurativeAction::getName() {
	return m_name;
}

float DurativeAction::getDuration(){
	return m_duration;
}

void DurativeAction::addParameters(Variable parameter) {
	m_parameters.push_back(parameter);
}

void DurativeAction::addCondition(Attribute att,Fluent *fluent) {	
	m_preconditions.push_back(make_pair(att,fluent));
}

void DurativeAction::addEffect(Attribute att,Fluent *fluent) {	
	m_effects.push_back(make_pair(att,fluent));
}

void DurativeAction::addDuration(float duration){
	m_duration=duration;
}

void DurativeAction::addNotCondition(Attribute att,Fluent *fluent){
	m_not_preconditions.push_back(make_pair(att,fluent));
}

void DurativeAction::addNotEffect(Attribute att,Fluent *fluent){
	m_not_effects.push_back(make_pair(att,fluent));
}

bool DurativeAction::isVariable(string name){
	for(vector<Variable >::iterator it= m_parameters.begin();it != m_parameters.end();++it){
		if (((*it).getName())==name) return true;
	}
	return false;
}

Variable * DurativeAction::getVariable(string name){
	for(vector<Variable >::iterator it= m_parameters.begin();it != m_parameters.end();++it){
		if (((*it).getName())==name) return &(*it);
	}
	return new Variable("j'aime pas les warning",vector<Type *> ());
}

//preconditions
vector< Fluent *> DurativeAction::getPreconditions(){
	vector< Fluent *> prec =vector< Fluent *>();
	for (vector< pair< Attribute,Fluent *> >::iterator it = m_preconditions.begin(); it != m_preconditions.end(); ++it){
		prec.push_back((*it).second);
	}
	return prec;
}

vector< Fluent *> DurativeAction::getEffectsF(){
	vector< Fluent *> eff =vector< Fluent *>();
	for (vector< pair< Attribute,Fluent *> >::iterator it = m_effects.begin(); it != m_effects.end(); ++it){
		eff.push_back((*it).second);
	}
	return eff;
}

bool DurativeAction::isPredConditions(string * name,vector<vector<Type *>> types){
	for (vector< pair< Attribute,Fluent *> >::iterator it_flu = m_preconditions.begin(); it_flu != m_preconditions.end(); ++it_flu) {
		if (((*name) == (*it_flu).second->getPredicate()->getName() ) && (equal(types.begin(), types.end(),(*it_flu).second->getPredicate()->getTypesList()->begin()) )) {
			return true;
		}
	}
	return false;
}

Fluent * DurativeAction::getPredCondition(string * name,vector<vector<Type *>> types){
	for (vector< pair< Attribute,Fluent *> >::iterator it_flu = m_preconditions.begin(); it_flu != m_preconditions.end(); ++it_flu) {
		if (((*name) == (*it_flu).second->getPredicate()->getName() ) && (equal(types.begin(), types.end(),(*it_flu).second->getPredicate()->getTypesList()->begin()) )) {
			return (*it_flu).second;
		}
	}
	return new Fluent(new Predicate("inexistant_1"));
}


//notprecondition
vector< Fluent *> DurativeAction::getNotPreconditions(){
	vector< Fluent *> prec =vector< Fluent *>();
	for (vector< pair< Attribute,Fluent *> >::iterator it = m_not_preconditions.begin(); it != m_not_preconditions.end(); ++it){
		prec.push_back((*it).second);
	}
	return prec;
}

bool DurativeAction::isPredNotConditions(string * name,vector<vector<Type *>> types){
	for (vector< pair< Attribute,Fluent *> >::iterator it_flu = m_not_preconditions.begin(); it_flu != m_not_preconditions.end(); ++it_flu) {
		if (((*name) == (*it_flu).second->getPredicate()->getName() ) && (equal(types.begin(), types.end(),(*it_flu).second->getPredicate()->getTypesList()->begin()) )) {
			return true;
		}
	}
	return false;
}

Fluent * DurativeAction::getPredNotCondition(string * name,vector<vector<Type *>> types){
	for (vector< pair< Attribute,Fluent *> >::iterator it_flu = m_not_preconditions.begin(); it_flu != m_not_preconditions.end(); ++it_flu) {
		if (((*name) == (*it_flu).second->getPredicate()->getName() ) && (equal(types.begin(), types.end(),(*it_flu).second->getPredicate()->getTypesList()->begin()) )) {
			return (*it_flu).second;
		}
	}
	return new Fluent(new Predicate("inexistant_2"));
}

vector<pair<Attribute, Fluent*> > DurativeAction::getPreconditions2() {
	return m_preconditions;
}

vector< pair<Attribute, Fluent *> > DurativeAction::getNotPreconditions2(){
	return m_not_preconditions;
}

vector<pair<Attribute, Fluent*> > DurativeAction::getEffects() {
	return m_effects;
}

vector<pair<Attribute, Fluent*> > DurativeAction::getNotEffects() {
	return m_not_effects;
}

vector<Variable >* DurativeAction::getParameters(){
	return &m_parameters;
}

string DurativeAction::to_string(){
	string rep="Action "+m_name;
	rep +="\n\tParam : ";
	for (vector<Variable>::iterator it = m_parameters.begin(); it != m_parameters.end();++it){
		rep +=" | "+(*it).getName();
	}
	if (m_preconditions.size() > 0){
		rep +="\n\t\tPrecondition : ";
		for (vector< pair< Attribute,Fluent *> >::iterator it =m_preconditions.begin(); it !=m_preconditions.end();++it){
			rep +=(*it).second->to_string()+"<->"+(*it).first.to_string()+" ;; " ;
		}
	}
	if (m_not_preconditions.size() > 0){
		rep +="\n\t\tNegative precondition : ";
		for (vector< pair< Attribute,Fluent *> >::iterator it =m_not_preconditions.begin(); it !=m_not_preconditions.end();++it){
			rep +=(*it).second->to_string()+"<->"+(*it).first.to_string();
		}
	}
	if (m_effects.size() > 0){
		rep +="\n\t\tAdd : ";
		for (vector< pair< Attribute,Fluent *> >::iterator it =m_effects.begin(); it !=m_effects.end();++it){
			rep +=(*it).second->to_string()+"<->"+(*it).first.to_string();
		}
	}
	if (m_not_effects.size() > 0){
		rep +="\n\t\tDelete : ";
		for (vector< pair< Attribute,Fluent *> >::iterator it =m_not_effects.begin(); it !=m_not_effects.end();++it){
			rep +=(*it).second->to_string()+"<->"+(*it).first.to_string();
		}
	}
	return rep;
}

string  DurativeAction::to_stringParam(){
	string rep="Action "+getName();
	rep +="\n\tParam : ";
	for (vector<Variable>::iterator it = m_parameters.begin(); it != m_parameters.end();++it){
		rep +=" | "+(*it).getName();
	}
	
	return rep;
}


//copy constructor

DurativeAction::DurativeAction(const DurativeAction &action){
	m_name=action.getNameC();
	m_parameters = vector<Variable>();
	for(unsigned i =0 ; i<action.getParametersC().size(); ++i){
		m_parameters.push_back(action.getParametersC().at(i));
	}
	m_preconditions=vector< pair<Attribute, Fluent *> >();
	for(unsigned i =0 ; i< action.getPreconditions2C().size(); ++i){
		m_preconditions.push_back(action.getPreconditions2C().at(i));
	}
	m_not_preconditions=vector< pair<Attribute, Fluent *> >();
	for(unsigned i =0 ; i< action.getNotPreconditions2C().size(); ++i){
		m_not_preconditions.push_back(action.getNotPreconditions2C().at(i));
	}
	m_effects=vector< pair<Attribute, Fluent *> >();
	for(unsigned i = 0 ; i< action.getEffectsC().size(); ++i){
		m_effects.push_back(action.getEffectsC().at(i));
	}
	m_not_effects=vector< pair<Attribute, Fluent *> >();
	for(unsigned i =0 ; i< action.getNotEffectsC().size(); ++i){
		m_not_effects.push_back(action.getNotEffectsC().at(i));
	}
}


vector<Variable >  DurativeAction::getParametersC()const{
	return m_parameters;
}

string DurativeAction::getNameC()const{
	return m_name;
}
	
vector< pair<Attribute, Fluent *> > DurativeAction::getPreconditions2C()const{
	return m_preconditions;
}

vector< pair<Attribute, Fluent *> > DurativeAction::getNotPreconditions2C()const{
	return m_not_preconditions;
}

vector< pair< Attribute,Fluent *> > DurativeAction::getEffectsC()const{
	return m_effects;
}

vector< pair< Attribute,Fluent *> > DurativeAction::getNotEffectsC()const{
	return m_not_effects;
}
