/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: 
 * Lionel Clément
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "synthesizer.hh"
#include "compact-lexicon.hh"
#include "compact-lexicon-buffer.hh"
#include "term.hh"
#include "statements.hh"
#include "statement.hh"
#include "messages.hh"
#include "environment.hh"
#include "forest.hh"
#include "item.hh"
#include "itemset.hh"
#include "listfeatures.hh"
#include "terms.hh"
#include "rule.hh"
#include "node.hh"
#include "vartable.hh"

/* **************************************************
 *
 ************************************************** */
Synthesizer::Synthesizer() {
   this->compactLexicon = NULL;
   this->maxLength = MAXLENGTH;
   this->maxUsages = MAXUSAGES;
   this->maxCardinal = MAXCARDINAL;
   this->nodeRoot = nodePtr();
   this->lexiconFileName = std::string();
   this->grammarFileName = std::string();
   this->inputFileName = std::string();
#ifdef OUTPUT_XML
   this->outXML = NULL;
#endif
   this->reduceAll = false;
   this->warning = false;
   this->random = false;
   this->attempsRandom = 1000;
   this->trace = false;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::~Synthesizer(void) {
   DELETE;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTrace(void) const {
   return trace;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTrace(bool trace) {
   this->trace = trace;
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::ItemSet_map::const_iterator Synthesizer::begin(void) const {
   return states.begin();
}

/* **************************************************
 *
 ************************************************** */
Synthesizer::ItemSet_map::const_iterator Synthesizer::end(void) const {
   return states.end();
}

/* **************************************************
 *
 ************************************************** */
size_t Synthesizer::size(void) const {
   return states.size();
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setInputFileName(char *name) {
   inputFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setLexiconFileName(char *name) {
   lexiconFileName = name;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactLexiconFileName(char *bufferName) {
   compactLexiconFileName = bufferName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactDirectoryName(char *DirectoryName) {
   compactDirectoryName = DirectoryName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setGrammarFileName(char *name) {
   grammarFileName = name;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getInputFileName(void) const {
   return inputFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getLexiconFileName(void) const {
   return lexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getCompactLexiconFileName(void) const {
   return compactLexiconFileName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getCompactDirectoryName(void) const {
   return compactDirectoryName;
}

/* **************************************************
 *
 ************************************************** */
std::string Synthesizer::getGrammarFileName(void) const {
   return grammarFileName;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxLength(unsigned int maxLength) {
   this->maxLength = maxLength;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxUsages(unsigned int maxUsages) {
   this->maxUsages = maxUsages;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setMaxCardinal(unsigned int maxCardinal) {
   this->maxCardinal = maxCardinal;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Synthesizer::getMaxCardinal(void) {
   return this->maxCardinal;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Synthesizer::getMaxUsages(void) {
   return this->maxUsages;
}

/* **************************************************
 *
 ************************************************** */
class CompactLexicon *
Synthesizer::getCompactLexicon(void) const {
   return compactLexicon;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setCompactLexicon(class CompactLexicon *compactLexicon) {
   this->compactLexicon = compactLexicon;
}

/* **************************************************
 *
 ************************************************** */
const bool Synthesizer::getReduceAll(void) const {
   return reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setReduceAll(const bool reduceAll) {
   this->reduceAll = reduceAll;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setRandom(const bool random) {
   this->random = random;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getRandom(void) const {
   return this->random;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Synthesizer::setOutXML(char *outXML)
{
   this->outXML = outXML;
}

/* **************************************************
 *
 ************************************************** */
char *
Synthesizer::getOutXML(void) const
{
   return this->outXML;
}
#endif

#ifdef TRACE_OPTION
/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceInit(bool traceInit)
{
   this->traceInit = traceInit;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceStage(bool traceStage)
{
   this->traceStage = traceStage;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceClose(bool traceClose)
{
   this->traceClose = traceClose;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceShift(bool traceShift)
{
   this->traceShift = traceShift;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceReduce(bool traceReduce)
{
   this->traceReduce = traceReduce;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::setTraceAction(bool traceAction)
{
   this->traceAction = traceAction;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceInit(void)
{
   return this->traceInit;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceStage(void)
{
   return this->traceStage;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceClose(void)
{
   return this->traceClose;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceShift(void)
{
   return this->traceShift;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceReduce(void)
{
   return this->traceReduce;
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::getTraceAction(void)
{
   return this->traceAction;
}

#endif

/* **************************************************
 *
 ************************************************** */
std::list<std::string> &Synthesizer::getInputs(void) {
   return this->inputs;
}

/* **************************************************
 *
 ************************************************** */
const bool Synthesizer::insertItemMap(const itemPtr item) {
   return this->itemMap.insert(std::make_pair(item->getId(), item)).second;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::eraseItemMap(const unsigned int id) {
   this->itemMap.erase(id);
}

/* **************************************************
 *
 ************************************************** */
itemPtr Synthesizer::getItemMap(const unsigned int id) {
   return this->itemMap[id];
}

/* **************************************************
 *
 ************************************************** */
nodePtr Synthesizer::getNodeRoot(void) {
   return nodeRoot;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::addInput(std::string input) {
   return this->inputs.push_back(input);
}

/* **************************************************
 *
 ************************************************** */
class ForestMap Synthesizer::getForestMap(void) {
   return this->forestMap;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::printState(std::ostream& outStream, itemSetPtr state) {
   outStream << "Q" << state->getId();
   state->print(outStream);
}

/* **************************************************
 *
 ************************************************** */
itemPtr Synthesizer::createItem(itemPtr item, unsigned int row) {
   itemPtr it = Item::create(item->getRule(), item->getIndex() + 1, item->getIndexTerms(),
         item->getStatements() ? item->getStatements()->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED) : statementsPtr());
   it->addRanges(item->getRanges());
   it->addRanges(row);
   it->addForestIdentifiers(item->getForestIdentifiers());
   it->setInheritedFeatures(item->getInheritedFeatures()->clone());
   it->setInheritedSonFeatures(item->getInheritedSonFeatures()->clone());
   it->setSynthesizedFeatures(item->getSynthesizedFeatures()->clone());
   it->setSynthesizedSonFeatures(item->getSynthesizedSonFeatures()->clone());
   it->setSeen(item->getSeen());
   return it;
}

#ifdef MEMOIZATION
/* **************************************************
 *
 ************************************************** */
std::string
Synthesizer::keyMemoization(itemPtr actualItem, itemPtr previousItem)
{
   return std::to_string(actualItem->getId()) + '.' + std::to_string(previousItem->getCurrentTerm()->getCode()) + actualItem->getSynthesizedFeatures()->peekSerialString();
}
#endif

/* **************************************************
 *
 ************************************************** */
void Synthesizer::clear() {
   states.clear();
   forestMap.clear();
   itemMap.clear();
#ifdef MEMOIZATION
   memoizedMap.clear();
#endif
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::close(Parser &parser, itemSetPtr state, unsigned int row) {
   bool modification;
   do {
      loop: modification = false;

      // Iterate through list
      for (ItemSet::const_iterator actualItem = state->begin(); actualItem != state->end() && !modification; ++actualItem) {

         if ((*actualItem)->isSetFlags(Flags::SEEN | Flags::BOTTOM))
            continue;

#ifdef TRACE_OPTION
         if (traceClose) {
            std::cout << "<H3>####################### CLOSE #######################</H3>" << std::endl;
            (*actualItem)->print(std::cout);
            std::cout << std::endl;
         }
#endif

         // X -> alpha • [Y] gamma
         if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
               && (*actualItem)->getCurrentTerms()->isOptional()) {

#ifdef TRACE_UNHIDE
            std::cout << "<H3>####################### UNHIDE #######################</H3>" << std::endl;
            (*actualItem)->print(std::cout);
            std::cout << std::endl;
#endif

            (*actualItem)->addFlags(Flags::SEEN);

            itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
            forestPtr forestFound = forestPtr();
            forestIdentifierPtr fi = ForestIdentifier::create(it->getCurrentTerm()->getCode(), std::string(), row, row);
            ForestMap::map::const_iterator forestMapIt = forestMap.find(fi);
            if (forestMapIt != forestMap.end()) {
               forestFound = forestMapIt->second;
               fi.reset();
               it->addForestIdentifiers(it->getIndex(), forestMapIt->first);
            }
            else {
               forestFound = Forest::create(Entry::create(it->getCurrentTerm()->getCode()), row, row);
               forestMap.insert(std::make_pair(fi, forestFound));
               it->addForestIdentifiers(it->getIndex(), fi);
            }
            it->setIndex((*actualItem)->getIndex() + 1);
            it->addRanges(row);
#ifdef TRACE_UNHIDE
            std::cout << "<H3>####################### UNHIDE: X -> alpha [Y] • gamma #######################</H3>" << std::endl;
            it->print(std::cout);
            std::cout << std::endl;
#endif
            if (!state->insert(it, this)) {
               UNEXPECTED
            }
            else {
               insertItemMap(it);
            }
            it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
            it->setRule((*actualItem)->getRule()->clone());
            it->setIndex((*actualItem)->getIndex());
            it->getCurrentTerms()->unsetOptional();
#ifdef TRACE_UNHIDE
            std::cout << "<H3>####################### UNHIDE: X -> alpha • Y gamma #######################</H3>" << std::endl;
            it->print(std::cout);
            std::cout << std::endl;
#endif
            if (!state->insert(it, this)) {
               UNEXPECTED
            }
            else {
               insertItemMap(it);
            }
            state->erase(*actualItem);
            eraseItemMap((*actualItem)->getId());
            goto loop;
         }

         // X -> alpha • Y1|Y2 beta
         if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() && !(*actualItem)->getCurrentTerms()->isOptional()
               && (*actualItem)->getCurrentTerms()->size() > 1) {

#ifdef TRACE_UNFOLD
            std::cout << "<H3>####################### UNFOLD #######################</H3>" << std::endl;
            (*actualItem)->print(std::cout);
            std::cout << std::endl;
#endif

            (*actualItem)->addFlags(Flags::SEEN);
            termsPtr terms = (*actualItem)->getCurrentTerms();
            for (unsigned int indexTerm1 = 0; indexTerm1 < terms->size(); ++indexTerm1) {
               itemPtr it = (*actualItem)->clone(Flags::SEEN | Flags::CHOOSEN | Flags::REJECTED);
               it->setRule((*actualItem)->getRule()->clone());
               it->setIndex((*actualItem)->getIndex());
               it->setCurrentTerms(Terms::create((*terms)[indexTerm1]));
               it->getIndexTerms()[(*actualItem)->getIndex()] = indexTerm1;

#ifdef TRACE_UNHIDE
               std::cout << "<H3>####################### UNFOLD: insert #######################</H3>" << std::endl;
               it->print(std::cout);
               std::cout << std::endl;
#endif
               if (!state->insert(it, this)) {
                  UNEXPECTED
               }
               else {
                  insertItemMap(it);
               }
            }
            state->erase((*actualItem));
            eraseItemMap((*actualItem)->getId());
            goto loop;
         }

         (*actualItem)->apply(state, parser, this);
         if ((*actualItem)->isSetFlags(Flags::BOTTOM)) {
            state->erase((*actualItem));
            eraseItemMap((*actualItem)->getId());
            goto loop;
         }
         // X -> alpha • Y gamma
         else if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
               && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional()
               && parser.getGrammar().isNonTerminal((*actualItem)->getCurrentTerm()) && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {

#ifdef TRACE_OPTION
            if (traceClose) {
               std::cout << "<H3>####################### CLOSE (X -> α • Y β) #######################</H3>" << std::endl;
               (*actualItem)->print(std::cout);
               std::cout << std::endl;
            }
#endif
            (*actualItem)->addFlags(Flags::SEEN);

            featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
            if (!inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()) {
               if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                  bool effect = false;
                  (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                  inheritedSonFeatures->deleteAnonymousVariables();
               }

               for (Grammar::ruleList::const_iterator iterRules = parser.getGrammar().getRules().begin(); iterRules != parser.getGrammar().getRules().end(); ++iterRules) {
                  if (((*iterRules)->getLhs()->getCode() == (*actualItem)->getCurrentTerm()->getCode())) {

                     itemPtr it;
                     (*iterRules)->incUsages(this);
                     it = Item::create((*iterRules)->clone(), 0, 0, (*iterRules)->getStatements() ? (*iterRules)->getStatements()->clone(0) : statementsPtr());
                     it->addRanges(row);
                     //it->_renameVariables(it->getId());
                     it->setInheritedFeatures(inheritedSonFeatures->clone());

#ifdef TRACE_OPTION
                     if (traceClose) {
                        std::cout << "<H3>####################### CLOSE (Y -> • γ) #######################</H3>" << std::endl;
                        it->print(std::cout);
                        std::cout << std::endl;
                     }
#endif

                     // record the item
                     ItemSet::const_iterator found = state->find(it);
                     if (found != state->end()) {
                        (*found)->addRef((*actualItem)->getId());
                        it.reset();
                     }
                     else {
                        it->addRef((*actualItem)->getId());
                        if (!state->insert(it, this)) {
                           UNEXPECTED
                        }
                        else {
                           insertItemMap(it);
                        }
                     }
                     modification = true;
                     (*actualItem)->addFlags(Flags::SEEN);
                  }
               }
            }
         }

         // X -> delta •
         else if ((*actualItem)->isCompleted()) {

#ifdef TRACE_OPTION
            if (traceReduce) {
               std::cout << "<H3>####################### REDUCE Y -> γ • (actual) #######################</H3>" << std::endl;
               (*actualItem)->print(std::cout);
               std::cout << std::endl;
            }
#endif
            (*actualItem)->addFlags(Flags::SEEN);
            if (!(*actualItem)->getSynthesizedFeatures()) {
               UNEXPECTED
            }
            else {
               if ((*actualItem)->getSynthesizedFeatures()->isNil()) {
                  if (warning) {
                     std::ostringstream oss;
                     oss << "null synthesized feature structure " << (*actualItem)->getFilename() << '(' << (*actualItem)->getLineno() << ')' << std::endl;
                     ERROR(oss.str());
                  }
                  (*actualItem)->setSynthesizedFeatures(Features::create());
               }
               if (!(*actualItem)->getSynthesizedFeatures()->isBottom()) {

                  // If Axiom reduced or debug Transients
                  if (reduceAll || (*actualItem)->getRefs().size() == 0) {
#ifdef TRACE_OPTION
                     if (traceReduce) {
                        std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                        (*actualItem)->print(std::cout);
                        std::cout << std::endl;
                     }
#endif

                     if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                        bool effect = false;
                        (*actualItem)->getEnvironment()->replaceVariables((*actualItem)->getSynthesizedFeatures(), effect);
                        if (effect) {
#ifdef TRACE_OPTION
                           if (traceReduce) {
                              std::cout << "<H3>####################### REDUCE S -> γ • (AXIOM REDUCED) #######################</H3>" << std::endl;
                              (*actualItem)->print(std::cout);
                              std::cout << std::endl;
                           }
#endif
                           UNEXPECTED
                        }
                        (*actualItem)->getSynthesizedFeatures()->deleteAnonymousVariables();
                     }

                     forestPtr forestFound = forestPtr();
                     forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getLhs()->getCode(),
                           ((*actualItem)->getSynthesizedFeatures() ? (*actualItem)->getSynthesizedFeatures()->peekSerialString() : std::string()), (*actualItem)->getRanges()[0],
                           row);
                     ForestMap::map::const_iterator forestMapIt = forestMap.find(fi);
                     if (forestMapIt != forestMap.end()) {
                        forestFound = (*forestMapIt).second;
                        fi.reset();
                     }
                     else {
                        forestFound = Forest::create(Entry::create((*actualItem)->getLhs()->getCode()), (*actualItem)->getRanges()[0], row);
                        forestMap.insert(std::make_pair(fi, forestFound));
                        nodePtr node = Node::create();
                        node->addForest(forestFound);
                        nodeRoot->addForest(forestFound);
                     }
                     nodePtr node = Node::create();
                     for (unsigned int k = 0; k < (*actualItem)->getForestIdentifiers().size(); ++k) {
                        ForestMap::map::const_iterator forestMapIt = forestMap.find((*actualItem)->getForestIdentifiers()[k]);
                        if (forestMapIt != forestMap.end()) {
                           node->getForests().push_back((*forestMapIt).second);
                        }
                     }
                     forestFound->addNode(node);
                  }
                  for (std::set<unsigned int>::const_iterator ref = (*actualItem)->getRefs().begin(); ref != (*actualItem)->getRefs().end(); ++ref) {
                     itemPtr previousItem = getItemMap(*ref);
                     if (!previousItem) {
                        UNEXPECTED
                     }
                     else {

#ifdef TRACE_OPTION
                        if (traceReduce) {
                           std::cout << "<H3>####################### REDUCE (X -> α • Y β) (previous) #######################</H3>" << std::endl;
                           previousItem->print(std::cout);
                           std::cout << std::endl;
                        }
#endif

#ifdef MEMOIZATION
                        std::string key = keyMemoization(*actualItem, previousItem);
                        auto memItem = memoizedMap.find(key);
                        // Is this shift action already done ?
                        if (memItem != memoizedMap.end()) {
                           std::list< memoizationValuePtr > result = memItem->second;
                           for (std::list< memoizationValuePtr >::const_iterator i = result.begin();
                                 i != result.end();
                                 ++i) {
                              // New item build
                              itemPtr it = createItem(previousItem, row);
                              it->setEnvironment(previousItem->getEnvironment() ? previousItem->getEnvironment()->clone() : environmentPtr());
                              it->getSynthesizedSonFeatures()->add(previousItem->getIndex(), (*i)->getFeatures());
                              //...
                              featuresPtr inheritedFeatures = it->getInheritedFeatures();
                              if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom()) {
                                 if (it->getEnvironment() && it->getEnvironment()->size() > 0) {
                                    bool effect = false;
                                    it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
                                    inheritedFeatures->deleteAnonymousVariables();
                                 }
                              }

                              it->addForestIdentifiers(previousItem->getIndex(), (*i)->getForestIdentifier());

#ifdef TRACE_MEMOIZATION
                              std::cout << "<H3>####################### MEMOIZED REDUCE (X -> α Y • β) #######################</H3>" << std::endl;
                              it->print(std::cout);
                              std::cout << std::endl;
#endif
                              it->setRefs(previousItem->getRefs());

                              ItemSet::const_iterator found = states[row]->find(it);
                              if (found != states[row]->end()) {
                                 (*found)->addRefs(previousItem->getRefs());
                                 it.reset();
                              }
                              else {
                                 if (!states[row]->insert(it, this)) {
                                    UNEXPECTED
                                 }
                                 else {
                                    insertItemMap(it);
                                    modification = true;
                                 }
                              }
                              (*actualItem)->addFlags(Flags::SEEN);
                           }
                        }
                        // This reduce action is new
                        else
#endif
                        {
                           itemPtr it = createItem(previousItem, row);
                           it->setEnvironment(previousItem->getEnvironment() ? previousItem->getEnvironment()->clone() : environmentPtr());
                           it->getSynthesizedSonFeatures()->add(previousItem->getIndex(), (*actualItem)->getSynthesizedFeatures()->clone());

                           //...
                           featuresPtr inheritedFeatures = it->getInheritedFeatures();
                           if (!inheritedFeatures->isNil() && !inheritedFeatures->isBottom()) {
                              if (it->getEnvironment() && it->getEnvironment()->size() > 0) {
                                 bool effect = false;
                                 it->getEnvironment()->replaceVariables(inheritedFeatures, effect);
                                 inheritedFeatures->deleteAnonymousVariables();
                              }
                           }

                           // On transmet le contexte de previousItem
                           nodePtr node = Node::create();
                           for (unsigned int k = 0; k < (*actualItem)->getForestIdentifiers().size(); ++k) {
                              ForestMap::map::const_iterator forestMapIt = forestMap.find((*actualItem)->getForestIdentifiers()[k]);
                              if (forestMapIt == forestMap.end()) {
                                 UNEXPECTED
                              }
                              forestPtr forest = (*forestMapIt).second;
                              node->getForests().push_back(forest);
                           }
                           forestPtr forestFound = forestPtr();
                           forestIdentifierPtr fi = ForestIdentifier::create((*actualItem)->getId(), std::string(), (*actualItem)->getRanges()[0], row);
                           ForestMap::map::const_iterator forestMapIt = forestMap.find(fi);
                           if (forestMapIt != forestMap.end()) {
                              forestFound = forestMapIt->second;
                              it->addForestIdentifiers(previousItem->getIndex(), forestMapIt->first);
                              fi.reset();
                           }
                           else {
                              forestFound = Forest::create(Entry::create((*actualItem)->getLhs()->getCode()), (*actualItem)->getRanges()[0], row);
                              forestMap.insert(std::make_pair(fi, forestFound));
                              it->addForestIdentifiers(previousItem->getIndex(), fi);
                           }
                           forestFound->addNode(node);
#ifdef TRACE_OPTION
                           if (traceReduce) {
                              std::cout << "<H3>####################### REDUCE (X -> α Y • β) #######################</H3>" << std::endl;
                              it->print(std::cout);
                              std::cout << std::endl;
                           }
#endif
                           if (trace && it->getTrace()) {
                              std::cout << "*** Reduce \n";
                              it->getRule()->print(std::cout, it->getIndex() - 1, false, false);
                              std::cout << " ... ";
                              it->getRule()->print(std::cout, it->getIndex(), false, false);
                              std::cout << std::endl;
                           }

                           ItemSet::const_iterator found = states[row]->find(it);
                           if (found != states[row]->end()) {
                              (*found)->addRefs(previousItem->getRefs());
                              it.reset();
                           }
                           else {
#ifdef MEMOIZATION
                              // tabulates this result
                              // std::string key = keyMemoization(*actualItem, previousItem);
                              memoizedMap.insert(key,
                                    (*it->getSynthesizedSonFeatures())[it->getIndex()-1],
                                    it->getForestIdentifiers()[it->getIndex()-1]);
#endif
                              // record the item
                              it->setRefs(previousItem->getRefs());
                              if (!states[row]->insert(it, this)) {
                                 UNEXPECTED
                              }
                              else {
                                 insertItemMap(it);
                                 modification = true;
                              }
                              (*actualItem)->addFlags(Flags::SEEN);
                           }
                        }
                     }
                  }
               }
            }
         }

         // X -> alpha • t beta
         else if ((*actualItem)->getRhs().size() > (*actualItem)->getIndex() && !(*actualItem)->isCompleted() && !(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()]
               && (*actualItem)->getCurrentTerms()->size() == 1 && !(*actualItem)->getCurrentTerms()->isOptional()
               && parser.getGrammar().isTerminal((*actualItem)->getCurrentTerm()) && !(*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()]->isNil()) {
         }

         else {
            (*actualItem)->successor(state, this, modification);
         }
      }
   }
   while (modification);
   for (ItemSet::const_iterator i = state->begin(); i != state->end(); ++i)
      (*i)->subFlags(Flags::SEEN);
}

/* **************************************************
 *
 ************************************************** */
bool Synthesizer::shift(class Parser &parser, itemSetPtr state, unsigned int row) {
   bool modificationOnce = false;
   bool modification;
   do {
      modification = false;

      // Iterate through list
      for (ItemSet::const_iterator actualItem = state->begin(); actualItem != state->end() && !modification; ++actualItem) {
         if ((*actualItem)->isSetFlags(Flags::SEEN))
            continue;
         if ((*actualItem)->isSetFlags(Flags::BOTTOM))
            continue;
         if ((*actualItem)->getCurrentTerms()) {
            featuresPtr inheritedSonFeatures = (*(*actualItem)->getInheritedSonFeatures())[(*actualItem)->getIndex()];
            if (!(*actualItem)->getForestIdentifiers()[(*actualItem)->getIndex()] && !(*actualItem)->getCurrentTerms()->isOptional() && (*actualItem)->getCurrentTerm()
                  && !inheritedSonFeatures->isNil() && !inheritedSonFeatures->isBottom()
                  && parser.getGrammar().getTerminals().find((*actualItem)->getCurrentTerm()->getCode()) != parser.getGrammar().getTerminals().end()) {

#ifdef TRACE_OPTION
               if (traceShift) {
                  std::cout << "<H3>####################### SHIFT (X -> α • ω β) where ω ∈ ℒ #######################</H3>" << std::endl;
                  (*actualItem)->print(std::cout);
                  std::cout << std::endl;
               }
#endif

               if ((*actualItem)->getEnvironment() && (*actualItem)->getEnvironment()->size() > 0) {
                  bool effect = false;
                  (*actualItem)->getEnvironment()->replaceVariables(inheritedSonFeatures, effect);
                  inheritedSonFeatures->deleteAnonymousVariables();
               }

               unsigned int pred = inheritedSonFeatures->assignPred();
               std::string form = inheritedSonFeatures->assignForm();
               /*
                std::cerr << "inheritedSonFeatures : ";
                inheritedSonFeatures->print(std::cerr);
                std::cerr << std::endl;
                std::cerr << "pred:" << pred << std::endl;
                std::cerr << "form:" << form << std::endl;
                //std::cerr << "POS : " << Vartable::intToStr((*actualItem)->getFirstCurrentTerm()->getCode()) << std::endl;
                */
               Parser::entries_map_map::const_iterator foundCode = parser.getLexicon().find((*actualItem)->getCurrentTerm()->getCode());
               if (foundCode != parser.getLexicon().end() && (foundCode->second->size() != 0)) {
                  Parser::entries_map *listPred = foundCode->second;
                  if (listPred) {
                     Parser::entries_map::const_iterator found;
                     // stages : // 1) : without PRED or FORM
                     // 2) : with FORM
                     // 3) : with PRED
                     bool cont = true;
                     for (unsigned int stage = 1; cont && (stage <= 3); ++stage) {
                        entriesPtr entries = entriesPtr();

                        // With FORM
                        if ((stage == 2) && (form.size() == 0))
                           continue;

                        // With PRED
                        if ((stage == 3) && (pred == UINT_MAX))
                           continue;

                        /*****
                         std::cerr << "stage : " << stage << "<BR>" << std::endl;
                         std::cerr << "pred : " << Vartable::intToStr(pred) << "<BR>" << std::endl;
                         std::cerr << "form : " << form << "<BR>" << std::endl;
                         **** */

                        switch (stage) {
                           case 1:
                              found = listPred->find(UINT_MAX);		// Without pred : UINT_MAX = > ...
                              if (found != listPred->end()) {
                                 entries = found->second;
                              }
                              else
                                 break;
                              break;
                           case 2:
                              found = listPred->find(0);		// IDENTITY : 0 = > ...
                              if (found != listPred->end())
                                 entries = found->second;
                              break;
                           case 3:
                              found = listPred->find(pred);		// pred = > ...
                              if (found != listPred->end())
                                 // Local lexicon
                                 entries = found->second;
                              else if (compactLexicon) {
                                 // Compact lexicon
                                 entries = findCompactLexicon(parser, (*actualItem)->getCurrentTerm()->getCode(), std::string(), pred);
                              }
                              break;
                        }
                        // Found !
                        if (entries) {
                           cont = false;
                           Entries::list::const_iterator entryIt = entries->begin();
                           int tryRandom = 0;
                           while (entryIt != entries->end()) {
                              entryPtr entry = *entryIt;
                              if (this->getRandom()) {
                                 if (tryRandom++ > attempsRandom)
                                    break;
                                 size_t rv = std::rand() / ((RAND_MAX + 1u) / entries->size());
                                 entry = entries->get(rv);
                              }
                              else {
                                 entry = *entryIt;
                                 ++entryIt;
                              }

                              featuresPtr entryFeatures = entry->getFeatures() ? entry->getFeatures()->clone() : featuresPtr();
                              statementsPtr entryStatements = statementsPtr();
                              environmentPtr env = (*actualItem)->getEnvironment() ? (*actualItem)->getEnvironment()->clone() : Environment::create();

                              // Filter !!
                              // entryFeatures subsumes ↑
                              if (stage == 2 || (entryFeatures && entryFeatures->subsumes(inheritedSonFeatures, env))) {

                                 // New item build
                                 itemPtr it = createItem(*actualItem, row);

                                 it->setEnvironment(env);

                                 featuresPtr resultFeatures = featuresPtr();
                                 statementPtr s = Statement::create();
                                 featuresPtr inheritedSonFeaturesCopy = inheritedSonFeatures->clone();
                                 featuresPtr entryFeaturesCopy = entryFeatures->clone();
                                 if (entryFeatures) {
                                    resultFeatures = s->unif(entryFeaturesCopy, inheritedSonFeaturesCopy, it);
                                 }
                                 else
                                    resultFeatures = inheritedSonFeaturesCopy;
                                 s.reset();
                                 if (resultFeatures) {
                                    if (it->getEnvironment() && (it->getEnvironment()->size() > 0)) {
                                       bool effect = false;
                                       it->getEnvironment()->replaceVariables(resultFeatures, effect);
                                    }
                                    resultFeatures->renameVariables(entry->getId());
                                 }

                                 //it->getSynthesizedSonFeatures()->add((*actualItem)->getIndex(), resultFeatures);
                                 it->getSynthesizedSonFeatures()->add((*actualItem)->getIndex(), entryFeaturesCopy);
                                 if (entryStatements)
                                    entryStatements->renameVariables(entry->getId());
                                 entryPtr word;
                                 if (stage == 2)
                                    word = Entry::create(entry->getCode(), UINT_MAX, form, resultFeatures);
                                 else {
                                    size_t found = entry->getForm().find('$');
                                    if (found != std::string::npos) {
                                       bool effect = false;
                                       it->getEnvironment()->replaceVariables(entry->getForm(), effect);
                                       word = Entry::create(entry->getCode(), entry->getCodePred(), entry->getForm(), resultFeatures);
                                    }
                                    else
                                       word = Entry::create(entry->getCode(), entry->getCodePred(), entry->getForm(), resultFeatures);
                                 }
                                 forestIdentifierPtr fi = ForestIdentifier::create(word->getId(), resultFeatures->peekSerialString(), row - 1, row);
                                 ForestMap::map::const_iterator forestMapIt = forestMap.find(fi);
                                 if (forestMapIt != forestMap.end()) {
                                    it->addForestIdentifiers((*actualItem)->getIndex(), (*forestMapIt).first);
                                    fi.reset();
                                    //std::cerr << "stage : " << stage << "<BR>" << std::endl;
                                    //std::cerr << "pred : " << Vartable::intToStr(pred) << "<BR>" << std::endl;
                                    //std::cout << "form : " << form << "<BR>" << std::endl;
                                 }
                                 else {
                                    forestMap.insert(std::make_pair(fi, Forest::create(word, row - 1, row)));
                                    it->addForestIdentifiers((*actualItem)->getIndex(), fi);
                                 }
                                 it->setRefs((*actualItem)->getRefs());

#ifdef TRACE_OPTION
                                 if (traceShift) {
                                    std::cout << "<H3>####################### SHIFT (X -> α ω • β) #######################</H3>" << std::endl;
                                    it->print(std::cout);
                                    std::cout << std::endl;
                                 }
#endif

                                 if (trace && it->getTrace()) {
                                    std::cout << "*** Shift " << entry->getForm() << std::endl;;
				    it->getRule()->print(std::cout, it->getIndex() - 1, false, false);
                                    std::cout << " ... ";
                                    it->getRule()->print(std::cout, it->getIndex(), false, false);
                                    std::cout << std::endl;
                                 }

                                 // record the item
                                 if (!states[row]->insert(it, this)) {
                                    UNEXPECTED
                                 }
                                 insertItemMap(it);
                                 modification = true;
                                 modificationOnce = true;
                                 (*actualItem)->addFlags(Flags::SEEN);
                                 if (this->getRandom()) {
                                    break;
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   while (modification);
   for (ItemSet::const_iterator i = state->begin(); i != state->end(); ++i)
      (*i)->subFlags(Flags::SEEN);
   return modificationOnce;
}

/* **************************************************
 *
 ************************************************** */
void Synthesizer::generate(class Parser &parser) {
#ifdef OUTPUT_XML
   extern xmlNodePtr xmlNodeRoot;
#endif
   states.clear();
   itemMap.clear();
   forestMap.clear();
   for (Grammar::ruleList::const_iterator iterRules = parser.getGrammar().getRules().begin(); iterRules != parser.getGrammar().getRules().end(); ++iterRules) {
      (*iterRules)->resetUsages();
   }

   std::ofstream outfile;
   nodeRoot = Node::create();
   itemSetPtr initState = ItemSet::create(0);
   std::list<rulePtr> *rules = parser.getGrammar().findRules(parser.getStartTerm());
   itemPtr it;
   for (std::list<rulePtr>::const_iterator rule = rules->begin(); rule != rules->end(); ++rule) {
      (*rule)->incUsages(this);
      it = Item::create(*rule, UINT_MAX, 0, (*rule)->getStatements() ? (*rule)->getStatements()->clone(0) : statementsPtr());
      it->addRanges(0);
      it->setInheritedFeatures(parser.getStartFeatures());
      //it->renameVariables(it->getId());
#ifdef TRACE_OPTION
      if (traceInit) {
         std::cout << "<H3>####################### INIT #######################</H3>" << std::endl;
         it->print(std::cout);
         std::cout << std::endl;
      }
#endif
      insertItemMap(it);
      initState->insert(it, this);
   }

   states.insert(std::make_pair(0, initState));
   close(parser, initState, 0);

   unsigned int i = 0;
   while (i <= maxLength) {

      itemSetPtr actualState = ItemSet::create(++i);
      states.insert(std::make_pair(i, actualState));
      if (!shift(parser, initState, i))
         break;
#ifdef TRACE_OPTION
      if (traceStage) {
         std::cout << "<H3>####################### STAGE " << initState->getId() << " #######################</H3>" << std::endl;
         initState->print(std::cout);
         std::cout << std::endl;
      }
#endif

      actualState->resetUsages();
      close(parser, actualState, i);
      initState = actualState;
   }

   if (i > maxLength) {
      ERROR("maxLength");
   }
   if ((i % 121) == 0) {
      std::cerr << "Length : " << i << std::endl;
   }

   nodeRoot->generate(this->getRandom());
#ifdef OUTPUT_XML
   if (outXML) {
      nodeRoot->toXML(xmlNodeRoot, xmlNodeRoot);
   }
#endif
}

/* **************************************************
 *
 ************************************************** */
const entriesPtr Synthesizer::findCompactLexicon(Parser &parser, const unsigned int code, const std::string codeStr, const unsigned int pred) {
   unsigned long int info = ~0UL;
   std::string str;
   if (code)
      str = Vartable::intToStr(pred) + "#" + Vartable::intToStr(code);
   else if (codeStr.size())
      str = Vartable::intToStr(pred) + "#" + codeStr;
   else
      str = Vartable::intToStr(pred);
   info = compactLexicon->searchStatic(compactLexicon->init, str);
   // in : pos#lemma
   // out : form#fs
#ifdef TRACE_LEXICON
   std::cout << "<H3>####################### FIND IN THE COMPACT LEXICON #######################</H3>" << std::endl;
   std::cout << "<DIV>" << std::endl;
   std::cout << str << " => ";
   compactLexicon->printResults(std::cout, info, 1);
   std::cout << "</DIV>" << std::endl;
   std::cout << std::endl;
#endif
   if (info != ~0UL) {
      entriesPtr entries = Entries::create();
      while (info != ~0UL) {
         std::string result = compactLexicon->buffer + (compactLexicon->info[info].getOffset());
         std::string form = result.substr(0, result.find("#"));
         std::string features = result.substr(result.find("#") + 1, -1);

         if (!parser.parseBuffer("#", features, "features")) {
            if (parser.getLocalFeatures()) {
               unsigned int pred = parser.getLocalFeatures()->assignPred();
               entryPtr localEntry = Entry::create(0, pred, std::string(), parser.getLocalFeatures());

               localEntry->setCode(code);
               localEntry->setForm(form);
               std::string localEntrySerialString = localEntry->peekSerialString();
               Parser::entry_map::iterator found = parser.getMapLocalEntry().find(localEntrySerialString);
               if (found != parser.getMapLocalEntry().end()) {
                  entries->add(found->second);
               }
               else {
                  parser.getMapLocalEntry().insert(std::make_pair(localEntrySerialString, localEntry));
                  entries->add(localEntry);
               }
            }
         }
         else {
            std::ostringstream oss;
            oss << "error: Illegal lexical entry: " << form << " " << Vartable::intToStr(code) << " " << result.substr(result.find("#") + 1, -1) << std::endl;
            throw oss.str();
         }
         if ((compactLexicon->info[info].isNext()))
            info = compactLexicon->info[info].getNext();
         else
            info = (unsigned long int)(~(0UL));
      }
      return entries;
   }
   else
      return entriesPtr();
}

