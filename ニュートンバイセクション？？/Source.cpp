#include <iostream>
#include <algorithm>
#include <limits>
#include <tuple>
//https://ja.wikipedia.org/wiki/二分法
//https://ja.wikipedia.org/wiki/ニュートン法


template<class T=double,class F,class FD>
T NewtonMethod(T X, F Fun, FD FunDash,std::size_t Lim=50) {
	T XN(0);

	std::size_t C = 0;
	while (std::abs(X-XN)>std::numeric_limits<T>::epsilon()*2) {
		XN = X;
		X = X - (Fun(X) / (FunDash(X)));
		if (C == Lim && Lim != 0) { break; }
		C++;
	}

	return X;

}
template<class T=double,class F,class FD>
std::tuple<T,T,T> NewtonMethod2(T X, F Fun, FD FunDash,std::size_t Lim=50) {
	T XN(0);
	T Min(std::numeric_limits<T>::max());
	T Max(std::numeric_limits<T>::min());
	std::size_t C = 0;
	while (std::abs(X-XN)>std::numeric_limits<T>::epsilon()*2) {
		XN = X;
		X = X - (Fun(X) / (FunDash(X)));
		if (C == Lim && Lim != 0) { break; }
		
		C++;
		Min = std::min(X, Min);
		Max = std::max(X, Max);
	}

	return { X,Min,Max };

}
template<class T=double,class F>
T BisectionMethod(T Low, T High, F Fun, std::size_t Lim = 50) {

	if (Low > High) std::swap(Low, High);


	T XN(0);
	T X = (Low + High) / 2;
	T SL = Fun(Low) > 0 ? 1 : -1;
	T SH = Fun(High) > 0 ? 1 : -1;

	std::size_t C = 0;

	X = (Low + High) / 2;
	T SM = Fun(X) > 0 ? 1 : -1;
	if (SM == SL) {
		Low = X;
	}
	else {
		High = X;
	}
	C++;
	while (std::abs(X-XN)>std::numeric_limits<T>::epsilon()*2) {
		if (C == Lim && Lim != 0) { break; }

		XN = X;
		X = (Low + High) / 2;
		T SM = Fun(X) > 0 ? 1 : -1;
		if (SM == SL) {
			Low = X;
		}
		else {
			High = X;
		}
		C++;
	}
	return X;
}
/** /
template<class T=double ,class BMF,class NMF,class NMFD>
T NewtonBisectionMethod(T X, BMF BMFun, NMF NMFun, NMFD NMFunDash,std::size_t Lim=50) {//maybe perfect answer.
	std::size_t C = 0;
	T XN(0);
	T L=std::numeric_limits<T>::min();
	T H=std::numeric_limits<T>::max();
	for(std::size_t i=0;i<7;i++){//7==prime. no meen is implimented.
		if (X == XN) break;
		XN = X;
		X = X - (NMFun(X) / (NMFunDash(X)));
		L = std::max(L, X);
		H = std::min(H, X);
		if (C == Lim && Lim != 0) { break; }
		C++;
	}
	return BisectionMethod(L, H, BMFun, Lim);
}
/**/
template<class T,class FB,class FN,class FND>
T SandWitchMagic(const T& Min, const T& Max, FB fb, FN fn, FND fnd, std::size_t N = 0) {//naming is poor mind.
	auto X = BisectionMethod(Min, Max, fb, N);
	auto [X2, Min2, Max2] = NewtonMethod2(X, fn, fnd, N);
	auto X3 = BisectionMethod(Min2, Max2, fb, N);

	return X3;
}
int main() {

	auto F = [](const auto& X) { return X * X - 2;  };//x^2=2 to x^2-2=0;
	auto FD = [](const auto& X) {return 2 * X; };
	/** /
	auto X = NewtonMethod(1.0, F, FD,12);
	auto X2 = BisectionMethod(0.0, 6.0, F);
//	auto X3 = NewtonBisectionMethod(1.0, F, F, FD);

	auto X4 = BisectionMethod(X - 0.5, X+0.5 , F);//value X have bias.
	/**/
	/** /
	auto X7 = BisectionMethod(0.0, 10.0, F,0);
	auto [X5, Min, Max] = NewtonMethod2(X7, F, FD,0);
	auto X6 = BisectionMethod(Min, Max, F,0);
	/**/
	auto X8 = SandWitchMagic(0.0, 10.0, F, F, FD,30);
	return 0;
}