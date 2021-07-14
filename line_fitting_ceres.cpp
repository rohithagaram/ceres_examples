#include <ceres/ceres.h>
#include <glog/logging.h>

using ceres::Solver;
using ceres::Solve;
using ceres::Problem;
using ceres::CostFunction;
using ceres::AutoDiffCostFunction;

// this programs finds the close point to (0,2) which satisfies  y= x^2 + 1

struct my_cost {

	my_cost(double x_actual, double y_actual)
		: x_(x_actual), y_(y_actual) {}
	template <typename T>
	bool operator () (const T* const slope, const T* const  intercept,T* residual) const {
		T y_pred;

		// y = slope*x + intercept
		y_pred = slope[0] * T(x_) + intercept[0];

		// Residual is the distance between the points
		residual[0] = sqrt((T(y_pred) - T(y_)) * (T(y_pred) - T(y_)));

		return true;
	}

private:
	// Observations for a sample.
	const double x_;
	const double y_;
};


int main(int argc, char** argv) {

	google::InitGoogleLogging(argv[0]);

	
	

	// Initial value of slope and intercept
	double slope = 2;
	double  intercept = 3;

	const double initial_slope = slope;
	const double inital_intercept = intercept;
	Problem problem;


	int numObs = 3;
	// set of observations
	int x_cor[3] = { 0,1,2};
	int y_cor[3] = { 6,0,0};
	for (int i = 0; i < numObs; ++i) {
		ceres::CostFunction  *mycost_o = new AutoDiffCostFunction<my_cost, 1, 1,1>(new my_cost(x_cor[i], y_cor[i]));
		problem.AddResidualBlock(mycost_o, nullptr, &slope, &intercept);
	}


	Solver::Options options;
	options.minimizer_progress_to_stdout = true;
	Solver::Summary summary;
	Solve(options, &problem, &summary);
	std::cout << summary.BriefReport() << "\n";
	std::cout << "x : " << initial_slope << " -> " << slope << "\n";
	std::cout << "y : " << inital_intercept << " -> " << intercept << "\n";
	return 0;



}