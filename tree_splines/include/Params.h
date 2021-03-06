/**
 * @File     : CHasse.h
 * @Authors  : C. Low-Kam, L. Di-Jorio
 * @Date     : 08/02/2006
 * @Version  : V1.0
 * @Synopsis : Hasse diagram structure, with associated operation
**/

#if !defined __PARAMS_H__
#define      __PARAMS_H__

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/symmetric.hpp>

#include <stdio.h>
#include <vector>

#define BNU boost::numeric::ublas

namespace nsTreeSplines
{
    class Params
    {
		public :
			int nb_indiv; // Number of individuals (I)
			int nb_dose; // Dose number (D)
			int nb_repeat; // Repeatition number (K)
			int nb_assay; // Assays number (J)
			int nb_time; // Time number (T)
			int nb_predictors; // Number of predictors
			int delta; // spline order
			int xi;
			int nb_loop; // Number of loop that the algorithm will make
			int nb_loop_train; // Number of loop that the algorithm will make to train (after this number, results are stored)
			int nb_test_indiv; // Number of individuals used for testing beta
			int nb_test_step; // Interval to test beta
			int max_depth;

			double * tau;
			double alpha, beta2; //TODO init in params
			double pgrow, pprune, pchange; // TODO init in params
			double a1, b1; //TODO change name of these one
			double lambda1, lambda2, lambda3;
			double w;

			double ** predictors; // Splitting predictors
			BNU::mapped_matrix<double> penalty_matrix; // Penalty matrix (K_{d+delta})
			BNU::mapped_matrix<double> spline_base_matrix; // Spline base matrix (B)
			double penalty_matrix_det; // Determinant of the penalty matrix
			double phi_d, phi_t; // correlation dose
			BNU::symmetric_matrix<double, BNU::lower> sigma_j; // covariance assay
			BNU::symmetric_matrix<double, BNU::lower> sigma_d; // covariance dose
			BNU::symmetric_matrix<double, BNU::lower> sigma_t; // covariance time
			BNU::symmetric_matrix<double> lambda;

			Params (void) throw ();
			~Params (void) throw ();

			// -------------------------------------- //
			//                METHODS                 //
			// -------------------------------------- //
			void ChooseSplitter (int & index, double & value) throw ();
			std::vector <int> GetAvailablePredictors (const std::vector <int> & indiv) throw ();
			std::vector <double> GetAvailableValues (const int & index) throw ();
			//BNU::matrix <double> GetSigma_d_Inv () throw ();
	};

	std::ostream& operator<< (std::ostream & os, nsTreeSplines::Params * params) throw ();
}

#undef BNU
#endif /* __PARAMS_H__ */
