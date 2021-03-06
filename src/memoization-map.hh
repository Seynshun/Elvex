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

#ifndef MEMOIZATIONMAP_H
#define MEMOIZATIONMAP_H

#include <string>
#include <list>
#include <unordered_map>
#include "memoization-value.hh"

class MemoizationMap:
      public std::enable_shared_from_this<class MemoizationMap> {

public:
   typedef std::unordered_map<std::string, std::list<memoizationValuePtr> > unordered_map;

private:
   unordered_map map;

public:
   void clear(void);
   unordered_map::const_iterator end(void) const;
   unordered_map::const_iterator find(const std::string) const;
   void insert(std::string, featuresPtr, forestIdentifierPtr);

};
#endif // MEMOIZATIONMAP_H
