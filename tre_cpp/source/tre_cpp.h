// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TRE_CPP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TRE_CPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TRE_CPP_EXPORTS
#define TRE_CPP_API __declspec(dllexport)
#else
#define TRE_CPP_API __declspec(dllimport)
#endif

// This class is exported from the tre_cpp.dll
namespace tre_cpp {
	class TRE_CPP_API Tre {
	public:
		Tre(void);

		/* For fuzzy searches, define "fuzziness" level */
		class TRE_CPP_API ApproximationOptions {
		public:
			/*Cost of an inserted character, that is, an extra character in string.*/
			int cost_ins = 1;
			/*Cost of a deleted character, that is, a character missing from string.*/
			int cost_del = 1;
			/*Cost of a substituted character.*/
			int cost_subst = 1;
			/*Maximum allowed cost of a match. If this is set to zero, an exact matching is searched for.*/
			int max_cost = 0;
			/*Maximum allowed number of inserted characters.*/
			int max_ins = 0;
			/*Maximum allowed number of deleted characters.*/
			int max_del = 0;
			/*Maximum allowed number of substituted characters.*/
			int max_subst = 0;
			/*Maximum allowed number of errors (inserts + deletes + substitutes).*/
			int max_err = 0;
		};
		/* Search options */
		class TRE_CPP_API RegexOptions {
		public:
			/*
				Use POSIX Extended Regular Expression (ERE) compatible syntax, default syntax is the POSIX Basic Regular Expression (BRE) syntax, but it is considered obsolete
			*/
			bool extendedRegex;
			/*
				Ignore case
			*/
			bool ignoreCase;
			/*
				Normally the newline character is treated as an ordinary character. When this flag is used, the newline character ('\n', ASCII code 10) is treated specially as follows:
				1. The match-any-character operator (dot "." outside a bracket expression) does not match a newline.
				2. A non-matching list ([^...]) not containing a newline does not match a newline.
				3. The match-beginning-of-line operator ^ matches the empty string immediately after a newline as well as the empty string at the beginning of the string (but see the REG_NOTBOL regexec() flag below).
				4. The match-end-of-line operator $ matches the empty string immediately before a newline as well as the empty string at the end of the string (but see the REG_NOTEOLregexec() flag below).
			*/
			bool newLine;
			/*
				Interpret the entire regex argument as a literal string, that is, all characters will be considered ordinary. This is a nonstandard extension, compatible with but not specified by POSIX.
			*/
			bool isLiteral;
			/*
				By default, repetition operators are greedy in TRE as per Std 1003.1-2001 (POSIX) and can be forced to be non-greedy by appending a ? character. This flag reverses this behavior by making the operators non-greedy by default and greedy when a ? is specified.
			*/
			bool ungreedy;
		};
		/* Result from search */
		class TRE_CPP_API SearchResult {
		public:
			/* Default constructor */
			SearchResult(size_t from, size_t to, const char* stringWithMatch);
			/* Copy constructor */
			SearchResult(const SearchResult & other);
			/*Move constructor*/
			SearchResult(SearchResult&& other);
			/*Copy assignment operator*/
			SearchResult& operator=(const SearchResult& other) &;
			/*Move assignment operator*/
			SearchResult& operator=(SearchResult&& other) &;
			/* Destructor */
			~SearchResult();
			/* Match startpoint */
			size_t from;
			/* Match endpoint */
			size_t to;
			/* Matching substring */
			const char * const match();
		private:
			/* Matching substring */
			char* pMatch;
		};

		/* For fuzzy searches, define "fuzziness" level */
		ApproximationOptions approximationOptions;
		/* Search options */
		RegexOptions searchOptions;
		/* The string where to search */
		const char* str;
		/* The regex search pattern */
		const char* regex;
		/* Perform the search */
		SearchResult search();
		/* Perform the search, inlines the definition of the regex pattern */
		SearchResult search(const char* regex);
		/* Perform the search, inlines the definition of the regex pattern and the string where to search */
		SearchResult search(const char* regex, const char* str);

		/*
		For fuzzy searches, define "fuzziness" level
		@param cost_ins: Cost of an inserted character, that is, an extra character in string.
		@param cost_del: Cost of a deleted character, that is, a character missing from string.
		@param cost_subst: Cost of a substituted character.
		@param max_cost: Maximum allowed cost of a match. If this is set to zero, an exact matching is searched for.
		@param max_ins: Maximum allowed number of inserted characters.
		@param max_del: Maximum allowed number of deleted characters.
		@param max_subst: Maximum allowed number of substituted characters.
		@param max_err: Maximum allowed number of errors (inserts + deletes + substitutes).
		*/
		void setApproximationOption(
			int cost_ins,
			int cost_del,
			int cost_subst,
			int max_cost,
			int max_ins,
			int max_del,
			int max_subst,
			int max_err
			);


		/*
		Set search options
		@param extendedRegex: Use POSIX Extended Regular Expression (ERE) compatible syntax, default syntax is the POSIX Basic Regular Expression (BRE) syntax, but it is considered obsolete.
		@param ignoreCase: Ignore case.
		@param newLine:
		Normally the newline character is treated as an ordinary character. When this flag is used, the newline character ('\n', ASCII code 10) is treated specially as follows:
		1. The match-any-character operator (dot "." outside a bracket expression) does not match a newline.
		2. A non-matching list ([^...]) not containing a newline does not match a newline.
		3. The match-beginning-of-line operator ^ matches the empty string immediately after a newline as well as the empty string at the beginning of the string (but see the REG_NOTBOL regexec() flag below).
		4. The match-end-of-line operator $ matches the empty string immediately before a newline as well as the empty string at the end of the string (but see the REG_NOTEOLregexec() flag below).
		@param isLiteral: Interpret the entire regex argument as a literal string, that is, all characters will be considered ordinary. This is a nonstandard extension, compatible with but not specified by POSIX.
		@param ungreedy: By default, repetition operators are greedy in TRE as per Std 1003.1-2001 (POSIX) and can be forced to be non-greedy by appending a ? character. This flag reverses this behavior by making the operators non-greedy by default and greedy when a ? is specified.
		*/
		void setSearchOptions(
			bool extendedRegex,
			bool ignoreCase,
			bool newLine,
			bool isLiteral,
			bool ungreedy
			);
	};

}
