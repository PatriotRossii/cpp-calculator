#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

#define M_REPEAT_1(function) function[0]
#define M_REPEAT_2(function) function[0], function[1]
#define M_REPEAT_3(function) function[0], function[1], function[2]
#define M_REPEAT_4(function) function[0], function[1], function[2], function[3]

#define M_EXPAND(...) __VA_ARGS__

#define M_REPEAT__(N, function) M_EXPAND(M_REPEAT_ ## N)(function)
#define M_REPEAT_(N, function) M_REPEAT__(N, function)
#define M_REPEAT(N, function) M_REPEAT_(M_EXPAND(N), function)

#define M_CALL(function, count) function(M_REPEAT(count, args))
#define M_FUNCTION_ENTRY_FULL(name, function, count) std::pair(std::string(#name), [](std::vector<double>& args) { return M_CALL(function, count); })
#define M_FUNCTION_ENTRY(name, count) std::pair(std::string(#name), [](std::vector<double>& args) { return M_CALL(std::name, count); })

class CalculatorState {
	std::unordered_map<std::string, std::function<double(std::vector<double>&)>> functions{
		// Basic operations
		M_FUNCTION_ENTRY(abs, 1), M_FUNCTION_ENTRY_FULL(mod, std::fmod, 2), M_FUNCTION_ENTRY_FULL(rem, std::remainder, 2),
		M_FUNCTION_ENTRY(fma, 3), M_FUNCTION_ENTRY_FULL(max, std::fmax, 2), M_FUNCTION_ENTRY_FULL(min, std::fmin, 2),
		M_FUNCTION_ENTRY_FULL(dim, std::fdim, 2),
		// Linear interpolation
		M_FUNCTION_ENTRY(lerp, 3),
		// Exponential functions
		M_FUNCTION_ENTRY(exp, 1), M_FUNCTION_ENTRY(exp2, 1), M_FUNCTION_ENTRY(expm1, 1),
		M_FUNCTION_ENTRY(log, 1), M_FUNCTION_ENTRY(log10, 1), M_FUNCTION_ENTRY(log2, 1),
		M_FUNCTION_ENTRY(log1p, 1),
		// Power functions
		M_FUNCTION_ENTRY(pow, 2), M_FUNCTION_ENTRY(sqrt, 1), M_FUNCTION_ENTRY(cbrt, 1),
		// Trigonometric functions
		M_FUNCTION_ENTRY(sin, 1), M_FUNCTION_ENTRY(cos, 1), M_FUNCTION_ENTRY(tan, 1),
		M_FUNCTION_ENTRY(asin, 1), M_FUNCTION_ENTRY(acos, 1), M_FUNCTION_ENTRY(atan, 1),
		M_FUNCTION_ENTRY(atan2, 2),
		// Hyperbolic functions
		M_FUNCTION_ENTRY(sinh, 1), M_FUNCTION_ENTRY(cosh, 1), M_FUNCTION_ENTRY(tanh, 1),
		M_FUNCTION_ENTRY(asinh, 1), M_FUNCTION_ENTRY(acosh, 1), M_FUNCTION_ENTRY(atanh, 1),
		// Error and gamma functions
		M_FUNCTION_ENTRY(erf, 1), M_FUNCTION_ENTRY(erfc, 1), M_FUNCTION_ENTRY(tgamma, 1),
		M_FUNCTION_ENTRY(lgamma, 1),
		// Nearest integer floating-point operations
		M_FUNCTION_ENTRY(ceil, 1), M_FUNCTION_ENTRY(floor, 1), M_FUNCTION_ENTRY(trunc, 1),
		M_FUNCTION_ENTRY(round, 1),
		// Floating-point manipulation functions
		M_FUNCTION_ENTRY(ldexp, 2), M_FUNCTION_ENTRY(scalbn, 2), M_FUNCTION_ENTRY(ilogb, 1),
		M_FUNCTION_ENTRY(logb, 1), M_FUNCTION_ENTRY(ldexp, 2)
	};
public:
	double invoke(const std::string& name, std::vector<double>& args) const {
		return functions.at(name)(args);
	}
};