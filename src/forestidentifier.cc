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

#include "forestidentifier.hh"
#include "vartable.hh"
#include "messages.hh"
#include "entry.hh"

/* ************************************************************
 *                                                            *
 ************************************************************ */
ForestIdentifier::ForestIdentifier(unsigned int code, const std::string featuresSerialString, unsigned int from, unsigned int to) {
   this->code = code;
   this->featuresSerialString = featuresSerialString;
   this->from = from;
   this->to = to;
   NEW;
}

/* **************************************************
 *
 ************************************************** */
ForestIdentifier::~ForestIdentifier() {
   DELETE;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
forestIdentifierPtr ForestIdentifier::create(unsigned int code, const std::string featuresSerialString, unsigned int from, unsigned int to) {
   return forestIdentifierPtr(new ForestIdentifier(code, featuresSerialString, from, to));
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::makeSerialString(void) {
   serialString = std::to_string(code);
   serialString += '[';
   serialString += from;
   serialString += '-';
   serialString += to;
   serialString += ']';
   serialString += featuresSerialString;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator <(const ForestIdentifier &o) const {
   return ((this->code < o.code) || (this->from < o.from) || (this->to < o.to) || (this->featuresSerialString < o.featuresSerialString));
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool ForestIdentifier::operator !=(const ForestIdentifier &o) const {
   return ((this->code != o.code) || (this->from != o.from) || (this->to != o.to) || (this->featuresSerialString != o.featuresSerialString));
}

/* **************************************************
 *
 ************************************************** */
void ForestIdentifier::print(std::ostream& out) const {
   out << "#" << code << '[' << from << '-' << to << ']';
}

/* **************************************************
 *
 ************************************************** */
size_t ForestIdentifier::hash::operator()(const forestIdentifierPtr i) const {
   return i->hashCode();
}

/* **************************************************
 *
 ************************************************** */
bool ForestIdentifier::equal_to::operator()(const forestIdentifierPtr i1, const forestIdentifierPtr i2) const {
   return i1->peekSerialString() == i2->peekSerialString();
}

