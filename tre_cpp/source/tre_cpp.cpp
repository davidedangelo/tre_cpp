// tre_cpp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "tre_cpp.h"
#include "tre.h"
#include <string>

namespace tre_cpp {

	const char NULL_CHAR = '\0';
	
	/* internals */
	regaparams_t getRegaParams(Tre::ApproximationOptions o) {
		return{
			o.cost_ins, o.cost_del, o.cost_subst, o.max_cost, o.max_ins, o.max_del, o.max_subst, o.max_err
		};
	}
	int getRegexFlags(Tre::RegexOptions o) {
		int r = 0;
		r = r + (o.extendedRegex ? REG_EXTENDED : 0);
		r = r + (o.ignoreCase ? REG_ICASE : 0);
		r = r + (o.newLine ? REG_NEWLINE : 0);
		r = r + (o.isLiteral ? REG_LITERAL : 0);
		r = r + (o.ungreedy ? REG_UNGREEDY : 0);
		return r;
	}

	/* public */
	Tre::Tre()
	{
		return;
	}

	Tre::SearchResult Tre::search()
	{
		int regexFlags = getRegexFlags(this->searchOptions);
		regaparams_t params = getRegaParams(this->approximationOptions);

		regmatch_t regmatch;
		regamatch_t regamatch{ 1, &regmatch };
		regex_t reg;

		tre_regcomp(&reg, regex, regexFlags);
		tre_regaexec(&reg, str, &regamatch, params, 0);

		size_t from = regmatch.rm_so;
		size_t to = regmatch.rm_eo;

		Tre::SearchResult r(from, to, str);

		return r;
	}

	Tre::SearchResult Tre::search(const char* regex)
	{
		this->regex = regex;
		return search();
	}

	Tre::SearchResult Tre::search(const char* regex, const char* str)
	{
		this->regex = regex;
		this->str = str;
		return search();
	}

	Tre::SearchResult::SearchResult(size_t from, size_t to, const char* stringWithMatch) {
		this->from = from;
		this->to = to;

		size_t strLen = strlen(stringWithMatch);

		if (from == to ||
			from > strLen ||
			to > strLen) {
			pMatch = new  char(NULL_CHAR);
		}
		else {
			size_t strSize = to - from;
			this->pMatch = new  char[strSize + 1];
			memcpy(pMatch, &(stringWithMatch[from]), strSize);
			this->pMatch[strSize] = NULL_CHAR;
		}

	}

	/* Copy constructor */
	Tre::SearchResult::SearchResult(const SearchResult & other)
	{
		this->from = other.from;
		this->to = other.to;

		size_t strSize = to - from;

		this->pMatch = new  char[strSize + 1];
		memcpy(this->pMatch, other.pMatch, strSize);
		this->pMatch[strSize] = NULL_CHAR;

	}
	/*Move constructor*/
	Tre::SearchResult::SearchResult(SearchResult &&other)
	{
		this->from = other.from;
		this->to = other.to;
		this->pMatch = other.pMatch;

		other.from = 0;
		other.to = 0;
		other.pMatch = nullptr;
		
	}
	/*Copy assignment operator*/
	Tre::SearchResult & Tre::SearchResult::operator=(const SearchResult &other) &
	{
		delete[] this->pMatch;

		this->from = other.from;
		this->to = other.to;

		size_t strSize = to - from;

		this->pMatch = new  char[strSize + 1];
		memcpy(this->pMatch, other.pMatch, strSize);
		this->pMatch[strSize] = NULL_CHAR;

		return *this;
	}
	/*Move assignment operator*/
	Tre::SearchResult & Tre::SearchResult::operator=(SearchResult &&other) &
	{
		delete[] this->pMatch;

		this->from = other.from;
		this->to = other.to;
		this->pMatch = other.pMatch;

		other.from = 0;
		other.to = 0;
		other.pMatch = nullptr;

		return *this;
	}
	/* Destructor */
	Tre::SearchResult::~SearchResult()
	{
		delete[] this->pMatch;
	}

	const char * const Tre::SearchResult::SearchResult::match() {
		return this->pMatch;
	};

	void Tre::setApproximationOption(int cost_ins, int cost_del, int cost_subst, int max_cost, int max_ins, int max_del, int max_subst, int max_err)
	{
		auto o = &this->approximationOptions;
		o->cost_del = cost_del;
		o->cost_ins = cost_ins;
		o->cost_subst = cost_subst;
		o->max_cost = max_cost;
		o->max_del = max_del;
		o->max_err = max_err;
		o->max_ins = max_ins;
		o->max_subst = max_subst;
	}

	void Tre::setSearchOptions(bool extendedRegex, bool ignoreCase, bool newLine, bool isLiteral, bool ungreedy)
	{
		auto o = &this->searchOptions;
		o->extendedRegex = extendedRegex;
		o->ignoreCase = ignoreCase;
		o->newLine = newLine;
		o->isLiteral = isLiteral;
		o->ungreedy = ungreedy;
	}

	

}