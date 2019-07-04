#include <iostream>
#include <algorithm>
#include <limits>
//https://ja.wikipedia.org/wiki/二分法
//https://ja.wikipedia.org/wiki/ニュートン法


template<class T=double,class F,class FD>
T NewtonMethod(T X, F Fun, FD FunDash,std::size_t Lim=50) {
	T XN(0);

	std::size_t C = 0;
	while (XN != X) {
		XN = X;
		X = X - (Fun(X) / (FunDash(X)));
		if (C == Lim && Lim != 0) { break; }
		C++;
	}

	return X;

}
template<class T=double,class F>
T BisectionMethod(T Low, T High, F Fun, std::size_t Lim = 50) {
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
	while (XN != X) {
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

template<class T=double ,class BMF,class NMF,class NMFD>
T NewtonBisectionMethod(T X, BMF BMFun, NMF NMFun, NMFD NMFunDash,std::size_t Lim=50) {//maybe perfect answer.
	std::size_t C = 0;
	T XN(0);
	T L=std::numeric_limits<T>::min();
	T H=std::numeric_limits<T>::max();
	for(std::size_t i=0;i<7;i++){//7==prime. good meen is not implimentation.
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

int main() {
	auto F = [](const auto& X) { return X * X - 2;  };
	auto FD = [](const auto& X) {return 2 * X; };

	auto X = NewtonMethod(1.0, F, FD,12);
	auto X2 = BisectionMethod(0.0, 6.0, F);
	auto X3 = NewtonBisectionMethod(1.0, F, F, FD);

	auto X4 = BisectionMethod(X - 1, X + 1, F);//value X have bias.

	return 0;
}