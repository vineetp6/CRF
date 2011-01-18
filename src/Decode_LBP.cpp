#include "CRF.h"

SEXP Decode_LBP(SEXP _crf, SEXP _maxIter, SEXP _cutoff, SEXP _verbose)
{
	CRF crf(_crf);

	PROTECT(_maxIter = AS_INTEGER(_maxIter));
	int maxIter = INTEGER_POINTER(_maxIter)[0];
	PROTECT(_cutoff = AS_NUMERIC(_cutoff));
	double cutoff = NUMERIC_POINTER(_cutoff)[0];
	PROTECT(_verbose = AS_INTEGER(_verbose));
	int verbose = INTEGER_POINTER(_verbose)[0];

	crf.Init_Labels();
	crf.Init_NodeBel();
	crf.Decode_LBP(maxIter, cutoff, verbose);

	UNPROTECT(3);
	return(crf._labels);
}

void CRF::Decode_LBP(int maxIter, double cutoff, int verbose)
{
	double *messages_1 = (double *) R_alloc(maxState * nEdges, sizeof(double)); // Messages from n2 to n1 at edge (n1, n2)
	double *messages_2 = (double *) R_alloc(maxState * nEdges, sizeof(double)); // Messages from n1 to n2 at edge (n1, n2)
	LoopyBP_max(messages_1, messages_2, maxIter, cutoff, verbose);
	Message2NodeBelief(messages_1, messages_2);
	MaxOfMarginals();
}
