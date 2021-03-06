/*!
 * \file tlpgp1.cpp
 * \brief [wip]Contains the core code of tlpgp1
 * \author Alan BENIER, Martin LAGLEIZE, Nathan PRAT
 * \version 1.0
 * \date Apr 23, 2014
 */

#include "tlpgp1.h"

Tlpgp1::Tlpgp1() {
	m_domainptr = nullptr;
	m_problemptr = nullptr;
}

Tlpgp1::Tlpgp1(Domain *domain, Problem *problem) :
				m_domainptr(domain), m_problemptr(problem) {
}

Tlpgp1::~Tlpgp1() {
	// TODO Auto-generated destructor stub
}

void Tlpgp1::constructGraph() {
	Graph1 m_graph2 = Graph1(m_domainptr, m_problemptr);
	m_graph2.generateGraph();
	m_vertex = m_graph2.getVertex();
	Fluent *f; //temp
	Attribute a; //temp

	//DurativeAction *act = graph2.findAction(m_vertex,graph2.getInits(),m_problemptr->getGoals()->at(1).first);
	//cout << act->to_stringParam() <<endl;
	//cout << graph2.getInits()->to_string() <<endl;
	//cout << graph2.getGoals()->to_string() <<endl;

	//graph2.getVertex()->toVector();

	cout << m_domainptr->getPredicates()->size() << endl;
	vertexToActions(); //convert the graph to a vector of vectors
	cout << "gggggggggggggggggg" << m_graph.size() << endl;

	//cout<<	m_graph[0][0]->to_stringParam() <<endl;
	//cout << m_graph.at(0)->to_stringParam() <<endl;
	//cout << m_graph.at(0)[0]->to_string() <<endl;

	for (int i = 0; i < m_graph.size(); ++i) {
		cout << "ccccc " << m_graph[i].size() << endl;
		for (auto it = m_graph[i].begin(); it != m_graph[i].end(); ++it) {
			cout << "actionaction" << (*it)->getName() << endl;
		}
	}
	//m_vertex->to_string();

	vector<Fluent *> goals = vector<Fluent *>();
	vector<Fluent *> inits = vector<Fluent *>();

	//for(auto it = graph2.getGoals()->getPreconditions().begin(); it != graph2.getGoals()->getPreconditions().end(); ++it)
	//cout << (*it)->to_string() <<endl;
	//goals.push_back(*it);

	//for(auto it = graph2.getGoals()->getNotPreconditions().begin(); it != graph2.getGoals()->getNotPreconditions().end(); ++it)
	//cout << (*it)->to_string() <<endl;
	//goals.push_back(*it);
	cout << "azzae" << endl;
	;
	cout << m_problemptr->getGoals()->size() << endl;
	;
	for (auto it = m_problemptr->getGoals()->begin();
			it != m_problemptr->getGoals()->end(); ++it) {
		cout << (*it).first->to_string() << "  aaa  "
				<< (*it).second.to_string() << endl;
		goals.push_back((*it).first);
	}
	cout << "vvsdsd" << goals.size() << endl;
	;

	for (auto it = m_problemptr->getInits()->begin();
			it != m_problemptr->getInits()->end(); ++it) {
		cout << (*it).first->to_string() << "  bbb  "
				<< (*it).second.to_string() << endl;
		inits.push_back((*it).first);
	}
	cout << "vdgsdsg" << inits.size() << endl;

	//Buts ← Pre(A G ) ;
	//DONE

	//TODO
	//Pour chaque effet e de Eff(A I ) :
	//Ajouter un intervalle I d’apparition de la proposition e à Agenda(e) ;
	//Fin pour;*/

	auto pos = goals.begin();
	pair<DurativeAction*, int> actA(nullptr, -2), actB(nullptr, -2);
	vector<Fluent *> tempGoals = vector<Fluent *>();
	int lvl = m_graph.size();
	vector<Member *> mlist = vector<Member *>();
	Constraint c;
	vector<Constraint> constraints;
	vector<pair<string, vector<IntervalAgenda>>> addAgenda, delAgenda;
	IntervalAgenda *inter;

	// backtraking requirements
	vector<Constraint> old_constraints;
	vector<pair<string, vector<IntervalAgenda>>> old_addAgenda, old_delAgenda;
	vector<Fluent *> old_goals;

	m_sat.initialize();

	declareFun(&m_sat);
	m_sat.postDeclareFun();

	cout << "ENTERING TLPGP1 CORE LOOP " << lvl << endl;
	lvl--;
	lvl--; //TODO remove
	// Tant que Buts ≠ ∅
	while (goals.size() != 0) {
		cout << "IN THE LOOP" << endl;
		//lvl--; //TODO remove

		// We CAN NOT iterate on goals and modifying it at the same time !
		tempGoals = goals;

		//Pour chaque précondition p d’une action B, p ∈ Buts :
		constraints = vector<Constraint>();
		for (auto it_goals = goals.begin(); it_goals != goals.end(); ++it_goals) {
			cout << "effet(it_goals) oo:" << (*it_goals)->to_string() << endl;
			actB = getActionByEffect(*it_goals, lvl, true, nullptr);
			if (actB.second == -1) {
				cout << "catastrophe&&&&" << endl;
				break;
			}
			cout << "action oo:" << actB.first->to_string() << endl;

			//constraints = vector<Constraint>();
			//sat.initialize();

			//declareFun(&sat);
			//sat.postDeclareFun();
			cout << "plopp " << endl;
			//cout << (*it_goals)->to_string()<<endl;

			//Buts ← Buts – p ;
			pos = find(tempGoals.begin(), tempGoals.end(), *it_goals);
			if (pos != tempGoals.end())
				tempGoals.erase(pos);
			cout << "tempGoals.sizetlpgp1 " << tempGoals.size() << endl;
			//printGoals(&tempGoals);

			//We save everything so we can backtrack later
			old_constraints = constraints;
			old_addAgenda = addAgenda;
			old_delAgenda = delAgenda;
			old_goals = goals;

			//Sélectionner (* point de backtrack *) en utilisant l'heuristique, une action A
			//qui produit p pour B ;
			// loop on b.getPreconditions()?

			backtrack:
			// if backtracking, select ANOTHER action

			actA = getActionByEffect(*it_goals, lvl, false, actB.first);
			if (actA.second == -1) {
				cout << "catastrophe" << endl;
				break;
			}
			//for(auto it_bPreconds = b.first->getPreconditions().begin(); it_bPreconds != b.first->getPreconditions().end(); ++it_bPreconds){
			//}

			float duration = actA.first->getEffects().at(0).first.getTime();
			//float duration = p.first->getDuration() //-> always 0?
			cout << "effet opo:" << (*it_goals)->to_string() << endl;
			cout << "b action opo:" << actB.first->to_string() << endl;
			cout << "selected action opo:  ::duration:: " << duration << " && "<< actA.first->to_string() << endl;

			//cout << p.first->to_string() <<" grre "<< p.second<<endl;

			//Buts ← Buts ∪ Pre(A) ;
			cout << "Pre(A).size() " << actA.first->getPreconditions2().size() << endl;
			//for(auto it_precondA = p.first->getPreconditions().begin(); it_precondA != p.first->getPreconditions().end(); ++it_precondA){
			for (int i = 0; i < actA.first->getPreconditions2().size(); ++i) {
				cout << "ttt " << endl;
				mlist =
						*actA.first->getPreconditions2().at(i).second->getMembersList();
				f =
						new Fluent(
								actA.first->getPreconditions2().at(i).second->getPredicate(),
								mlist);
				//cout << f->to_string() <<endl; //=fluent
				a = actA.first->getPreconditions2().at(i).first;
				//cout << a.to_string() <<endl; //=supported on

				tempGoals.push_back(f);
				cout << "goals pushback " << tempGoals.size() << endl;
				//printGoals(&tempGoals);
			}
			//cout << p.first->getNotPreconditions().size() <<endl;

			//Poser une contrainte de précédence entre A et B ;
			// τs(A)+δ1 ≤ τs(B)+δ2
			//c = Constraint("a", 1, "<", "b", 2);
			//c.print();
			string nameLeft = "", nameRight = "";
			nameLeft = actionToName(actA.first, actA.second);
			/*nameLeft += actA.first->getName() + "LVL" + to_string(actA.second); // Action a is one level below action b
			for (unsigned k = 0; k < actA.first->getParameters()->size(); ++k) {
				nameLeft += actA.first->getParameters()->at(k).getName();
			}*/
			cout << "nameLeft " << nameLeft << " vs " << actionToName(actA.first, actA.second) <<endl;
			cout << "tonameleft " << actionNameToName(nameLeft) <<endl;
			cout << "actionleft " << getActionByName(actionNameToName(nameLeft))->to_string() <<endl;
			/*nameRight += actB.first->getName() + "LVL" + to_string(actB.second);
			for (unsigned k = 0; k < actB.first->getParameters()->size(); ++k) {
				nameRight += actB.first->getParameters()->at(k).getName();
			}*/
			nameRight = actionToName(actB.first, actB.second);
			cout << "nameRight " << nameRight << " vs " << actionToName(actB.first, actB.second) <<endl;

			//c = Constraint(nameLeft, p.first->getDuration(), "<", nameRight, 0);
			c = Constraint(nameLeft, duration, "<", nameRight, 0);
			constraints.push_back(c);
			//sat.addConstraint(&c);
			//cout << "action:azdvxe"<< p.first->to_string() <<endl;
			//cout << "cstr:azdvxe";
			//c.print();
			//c = Constraint("zzz", 1, "<", "b", 2);
			//sat.addConstraint(&c);

			//Poser un intervalle I de maintien de précondition à Agenda(p) ;
			// ex: [ts(C3)+1; tG ] a agenda de p
			string agendaP = fluentToAgendaName(*it_goals);
			cout << " agendaP " << agendaP << endl;
			inter = new IntervalAgenda('[', nameLeft, duration, nameRight, 0, ']');
			addToAgenda(&addAgenda,(*it_goals)->getPredicate()->getName(),inter);
			cout << "inter fgt: " << inter->toString() <<endl;

			//Pour chaque intervalle I’ appartenant à Agenda(¬p) :
			//Poser une contrainte interdisant le recouvrement de I et I’.
			//ex: (τs(B)+δ2 ≤ τs(C)+δ3 ) ∨ (τs(D)+δ4 ≤ τs(A)+δ1 )
			//Fin pour ;
			/*
			 * I=[τ s (A)+δ 1 , τ s (B)+δ 2 ] et
			I'=[τ s (C)+δ 3 , τ s (D)+δ 4 ] sur lesquels une proposition et sa négation sont respectivement vraies
			peuvent être disjonctives. Dans le cas général, ces contraintes sont de la forme
			(τ s (B)+δ 2 ≤ τ s (C)+δ 3 ) ∨ (τ s (D)+δ 4 ≤ τ s (A)+δ 1 ).
			 *
			 */
			//vector<IntervalAgenda> tempAgenda = getIntervalsFromAgenda(&delAgenda, (*it_goals)->getPredicate()->getName());
			vector<IntervalAgenda> tempAgenda = getIntervalsFromAgenda(&delAgenda, agendaP);
			Constraint *leftC,*rightC;
			if(tempAgenda.size() != 0){
				cout << "lll " << endl;
				for(auto it_inter = tempAgenda.begin(); it_inter != tempAgenda.end(); ++it_inter){
					leftC = new Constraint(inter->getRightAction(), inter->getTimeRight(), "<", (*it_inter).getLeftAction(), (*it_inter).getTimeLeft());
					rightC = new Constraint((*it_inter).getRightAction(), (*it_inter).getTimeRight(), "<", inter->getLeftAction(), inter->getTimeLeft());
					m_sat.addDisjonctiveConstraint(leftC,rightC);
				}
			}
			else{
				cout << "nope lll " << endl;
			}

			//Pour chaque effet e de A, (sauf pour p lorsque le label de p est un
			//singleton) :
			cout << " yupjk " << actA.first->getEffectsF().size() << endl;
			cout << " yupjk " << actA.first->getEffectsF().at(0)->to_string() << endl;
			//for( auto it_effects = actA.first->getEffectsF().begin(); it_effects != actA.first->getEffectsF().end(); ++it_effects){
			for( int i = 0; i < actA.first->getEffectsF().size(); ++i){
				//Ajouter un intervalle I d’apparition de la proposition e à Agenda(e) ;
				// [ts(C3)+1] est ajouté à Agenda(¬b) pour prendre en compte l'apparition de l'effet ¬b.
				//string agendaE =""+actA.first->getEffectsF().at(0)->getPredicate()->getName()+actA.first->getEffectsF().at(0)->getMembersList()->at(0)->getName();
				//string agendaE = fluentToAgendaName(*it_effects);
				string agendaE = fluentToAgendaName(actA.first->getEffectsF().at(i));
				cout << " agendaE " << agendaE << endl;
				//addToAgenda(&addAgenda,(*it_effects)->getPredicate()->getName(),inter);
				addToAgenda(&addAgenda,agendaE,inter);

				//Pour chaque intervalle I’ de Agenda(¬e) :
				//Poser une contrainte interdisant le recouvrement de I et I’.
				//vector<IntervalAgenda> tempAgenda = getIntervalsFromAgenda(&delAgenda, (*it_effects)->getPredicate()->getName());
				vector<IntervalAgenda> tempAgenda = getIntervalsFromAgenda(&delAgenda, agendaE);
				Constraint *leftC,*rightC;
				cout << " tempAgenda.size() " << tempAgenda.size() << endl;
				if(tempAgenda.size() != 0){
					cout << " dsgsd dsf inloop" << endl;
					for(auto it_inter = tempAgenda.begin(); it_inter != tempAgenda.end(); ++it_inter){
						leftC = new Constraint(inter->getRightAction(), inter->getTimeRight(), "<", (*it_inter).getLeftAction(), (*it_inter).getTimeLeft());
						rightC = new Constraint((*it_inter).getRightAction(), (*it_inter).getTimeRight(), "<", inter->getLeftAction(), inter->getTimeLeft());
						m_sat.addDisjonctiveConstraint(leftC,rightC);
					}
				}
				//Fin pour ;
			}
			//Fin pour ;


			//cout << "constraints size xxaz " << constraints.size() << endl;
			printConstraints(&constraints);

			//Vérifier la consistance de Contraintes (appel au solveur DTP) ;
			//action A ;
			//sat.initialize();
			//declareFun(&sat);
			//sat.postDeclareFun();
			m_sat.addConstraints(&constraints);

			//En cas d’échec, retour au point de backtrack pour sélectionner une autre
			if(!m_sat.solve()){
				//we restore what is needed
				/*constraints = old_constraints ;
				addAgenda = old_addAgenda;
				delAgenda = old_delAgenda;
				goals = old_goals;

				//we backtrack
				goto backtrack;*/
			}
		}

		goals = tempGoals;

		//sat.addConstraints(&constraints);
		//sat.solve();

		//goals.clear();//TODO remove
		//break;
	}

	//sat.solve();

	//Si Contraintes est consistant
	if(m_sat.solve()){
		//Alors retourner le plan-solution flottant (actions sélectionnées et Contraintes)
	}
	else{
		//Sinon il n'y a pas de solution à ce niveau du graphe ;
		cout << "\n***  ECHEC TLPGP1  ***" <<endl;
	}
	//Fin si ;

	//Fin. TLPGP1
}

bool Tlpgp1::addToAgenda(vector<pair<string, vector<IntervalAgenda>>> *agenda, string effectName, IntervalAgenda *inter){
	for(auto it = agenda->begin(); it != agenda->end(); ++it){
		if ((*it).first == effectName){ //we are at the good spot
			(*it).second.push_back(*inter);
			return true;
		}
	}
	vector<IntervalAgenda> vect;
	vect.push_back(*inter);
	pair<string, vector<IntervalAgenda>> *p = new pair<string, vector<IntervalAgenda>>(effectName,vect);
	agenda->push_back(*p);
	return false;
}

vector<IntervalAgenda> Tlpgp1::getIntervalsFromAgenda(vector<pair<string, vector<IntervalAgenda>>> *agenda, string effectName){
	for(auto it = agenda->begin(); it != agenda->end(); ++it){
		if ((*it).first == effectName){ //we are at the good spot
			return (*it).second;
		}
	}
	return vector<IntervalAgenda>();
}

string Tlpgp1::fluentToAgendaName(Fluent *f){
	//cout << "(fluentToAgendaName) "<< f->to_string();
	string res = "";
	res += f->getPredicate()->getName();
	for(auto it = f->getMembersList()->begin(); it != f->getMembersList()->end(); ++it){
		res += (*it)->getName();
	}
	return res;
}

void Tlpgp1::vertexToActions() {
	cout << "aaaaaaaaaaaaaa" << m_vertex->getActions()->size() << endl;
	vector<DurativeAction *> * act = m_vertex->getFather()->getActions();
	cout << "aaaaaaaaaaaaaa" << act->size() << endl;

	//m_graph = vector<vector<DurativeAction* >> (10);
	m_graph.clear();

	Vertex * vertex = new Vertex(m_vertex);
	int state = 0;
	do {
		vertex = vertex->getFather();
		//cout<<"\zzzzzzzzzzzzzzzz "<<state<<"nbaction : "<<vertex->getActions()->size()<<"\n";
		/*for(vector<DurativeAction *>::iterator it = vertex->getActions()->begin() ; it != vertex->getActions()->end() ; ++it){
		 //cout<<"qqqqqqqqqqqqqq "<<(*it)->to_string()<<"\n";
		 m_graph[state].push_back(*it);
		 }*/
		m_graph.push_back(*(vertex->getActions()));
		state++;

	} while (vertex->getFather() != NULL);

	reverse(m_graph.begin(), m_graph.end());
	//m_graph.pop_back();

}

//TODO actionname = actionToName(DurativeAction *act, int level)
string Tlpgp1::actionToName(DurativeAction *act, int level){
	string res = "";
	res += act->getName()+"LVL"+to_string(level);
	for (unsigned k = 0; k < act->getParameters()->size(); ++k) {
		res += act->getParameters()->at(k).getName();
	}
	return res;
}



//TODO ? DurativeAction* ~= actionNameToAction(string name)
//std::size_t found = str.find(str2);
//  if (found!=std::string::npos)
//    std::cout << "first 'needle' found at: " << found << '\n';
string Tlpgp1::actionNameToName(string name){
	size_t found = name.find("LVL");
	if (found != string::npos){
		return string(name,0,found);
	}
	return "";
}

DurativeAction* Tlpgp1::getActionByName(string actionname){
	//string name = actionNameToName(actionname);
	for (int i = 0; i < m_graph.size(); ++i) {
		for (int j = 0; j < m_graph.at(i).size(); ++j) {
			if(m_graph.at(i).at(j)->getName() == actionname){
				/*for(auto it = m_graph.at(i).at(j)->getParameters()->begin(); it != m_graph.at(i).at(j)->getParameters()->end(); ++it){

				}*/
				return m_graph.at(i).at(j);
			}
		}
	}
	return nullptr;
}

//TODO string Tlpgp1::getActionByEffect(Fluent *effect, bool sameLevel, vector<DurativeAction*> forbiddenActions) {
pair<DurativeAction*, int> Tlpgp1::getActionByEffect(Fluent *effect, int level, bool sameLevel, DurativeAction* act) {
	if (sameLevel) {
		for (auto it_act = m_graph.at(level).begin(); it_act != m_graph.at(level).end(); it_act++){
			if (m_graph2.compareFVF2((*it_act)->getEffectsF(), effect))
				return make_pair(*it_act, level);
		}
		return make_pair(nullptr, -1);
	} else {
		for (auto it_act = m_graph.at(level - 1).begin(); it_act != m_graph.at(level - 1).end(); it_act++) {
			if(act->getName() != (*it_act)->getName()){
				//cout <<"getActionByEffect false "<< act->getName() << " " << (*it_act)->getName() <<endl;
				if (m_graph2.compareFVF2((*it_act)->getEffectsF(), effect))
					return make_pair(*it_act, level - 1);
			}
		}
		//return make_pair(nullptr, -1); //TODO remove (debug)
		return make_pair(act, -2);
	}
}

//Given an action, returns another action producing the required precondtitions
/*pair<DurativeAction*, int> Tlpgp1::selectAction(DurativeAction* action, int level) {

	for (auto it_act = m_graph.at(level-1).begin(); it_act != m_graph.at(level-1).end(); ++it_act) {
		if (m_graph2.compareFVF2((*it_act)->getEffectsF(), *action->getPreconditions()))
			return make_pair(*it_act, level);
	}
	return make_pair(nullptr, -1);
}*/

void Tlpgp1::removeGoals(Fluent *fluent, vector<Fluent*> *goals) {
	auto pos = goals->begin();
	//pos = find(goals->begin(), goals->end(), *goals);
	goals->erase(pos);
	//for(auto it_precond = goals->begin(); it_precond != goals->end(); ++it_precond){
	//}
}

void Tlpgp1::printGoals(vector<Fluent*> *goals) {
	cout << "printGoals: " << endl;
	for (auto it_goals = goals->begin(); it_goals != goals->end(); ++it_goals) {
		cout << (*it_goals)->to_string() << endl;
	}
	cout << "end printGoals: \n" << endl;
}

void Tlpgp1::printConstraints(vector<Constraint> *constraints) {
	cout << "printConstraints: " << endl;
	for (auto it_constraints = constraints->begin();
			it_constraints != constraints->end(); ++it_constraints) {
		(*it_constraints).print();
	}
	cout << "end printConstraints: \n" << endl;
}

void Tlpgp1::declareFun(Sat *s) {
	string name = "";
	for (int i = 0; i < m_graph.size(); ++i) {
		for (int j = 0; j < m_graph.at(i).size(); ++j) {
			name = "";
			name += m_graph.at(i).at(j)->getName() + "E" + to_string(i);
			for (unsigned k = 0;
					k < m_graph.at(i).at(j)->getParameters()->size(); ++k) {
				name += m_graph.at(i).at(j)->getParameters()->at(k).getName();
			}
			s->addFun(name);
		}
	}
	//cin >> name;
}

