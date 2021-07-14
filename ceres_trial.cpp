#include <ceres/ceres.h>
#include <glog/logging.h>

using ceres::Solver;
using ceres::Solve;
using ceres::Problem;
using ceres::CostFunction;
using ceres::AutoDiffCostFunction;

// this programs finds the close point to (0,2) which satisfies  y= x^2 + 1

struct my_cost {

	// x_actual=0, y_actual=2 in our case
	my_cost(double x_actual, double y_actual)
		: x_(x_actual), y_(y_actual) {}
	template <typename T>
	bool operator () (const T* const x, T* residual) const {
		T y_pred;

		// y = x^2 + 1
		y_pred = (T(x[0]) * T(x[0])) + T(1.0);

		// Residual is the distance between the points
		residual[0] = sqrt((x_ - T(x[0])) * (x_ - T(x[0])) + (y_ - y_pred) * (y_ - y_pred));

		return true;
	}

	private:
		// Observations for a sample.
		const double x_;
		const double y_;
};


int main(int argc , char** argv) {

	google::InitGoogleLogging(argv[0]);

	// point 0, 2
	double x_actual = 0;
	double y_actual = 2;
	// /////////////////////////////////////////////////////

	// Initial value of x
	double x = 2;

	const double initial_x = x;
	Problem problem;

	// Cost function
	// we have 1,1 in autoDiff as we have 1 x value and 1 residual
	// x_actual and y_actual is the point whose distance we wish to minimize
	CostFunction* mycost_o = new AutoDiffCostFunction<my_cost, 1, 1>(new my_cost(x_actual, y_actual));
	problem.AddResidualBlock(mycost_o, nullptr, &x);


	Solver::Options options;
	options.minimizer_progress_to_stdout = true;
	Solver::Summary summary;
	Solve(options, &problem, &summary);
	std::cout << summary.BriefReport() << "\n";
	std::cout << "x : " << initial_x << " -> " << x << "\n";
	std::cout << "y : " << initial_x * initial_x + 1 << " -> " << x * x + 1 << "\n";
	return 0;


	
}