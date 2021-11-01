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

#define call(function, count) function(M_REPEAT(count, args))
#define function_entry_full(name, function, count) std::pair(std::string(#name), [](std::vector<double> args) { return call(function, count); })
#define function_entry(name, count) std::pair(std::string(#name), [](std::vector<double> args) { return call(std::name, count); })

class CalculatorState {
	std::unordered_map<std::string, std::function<double(std::vector<double>)>> functions{
		// Basic operations
		function_entry(abs, 1), function_entry_full(mod, std::fmod, 2), function_entry_full(rem, std::remainder, 2),
		function_entry(fma, 3), function_entry_full(max, std::fmax, 2), function_entry_full(min, std::fmin, 2),
		function_entry_full(dim, std::fdim, 2),
		// Linear interpolation
		function_entry(lerp, 3),
		// Exponential functions
		function_entry(exp, 1), function_entry(exp2, 1), function_entry(expm1, 1),
		function_entry(log, 1), function_entry(log10, 1), function_entry(log2, 1),
		function_entry(log1p, 1),
		// Power functions
		function_entry(pow, 2), function_entry(sqrt, 1), function_entry(cbrt, 1),
		// Trigonometric functions
		function_entry(sin, 1), function_entry(cos, 1), function_entry(tan, 1),
		function_entry(asin, 1), function_entry(acos, 1), function_entry(atan, 1),
		function_entry(atan2, 2),
		// Hyperbolic functions
		function_entry(sinh, 1), function_entry(cosh, 1), function_entry(tanh, 1),
		function_entry(asinh, 1), function_entry(acosh, 1), function_entry(atanh, 1),
		// Error and gamma functions
		function_entry(erf, 1), function_entry(erfc, 1), function_entry(tgamma, 1),
		function_entry(lgamma, 1),
		// Nearest integer floating-point operations
		function_entry(ceil, 1), function_entry(floor, 1), function_entry(trunc, 1),
		function_entry(round, 1),
		// Floating-point manipulation functions
		function_entry(ldexp, 2), function_entry(scalbn, 2), function_entry(ilogb, 1),
		function_entry(logb, 1), function_entry(ldexp, 2),
	};
};