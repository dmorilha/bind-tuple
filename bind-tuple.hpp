#ifndef BIND_TUPLE_HPP
#define BIND_TUPLE_HPP

#include <tuple>
namespace ext {
	using std::declval;
	using std::get;
	using std::tuple;

	//copied awesome solution from http://stackoverflow.com/a/7858971
	namespace {
		template < int ... > struct seq { };
		template < int N, int ... S > struct gens : gens< N - 1, N - 1, S... > { };
		template < int ... S > struct gens< 0, S... > { typedef seq< S... > type; };
	}

	template < typename F >
	class FunctionBinder {
	protected:
		const F & f;

		template < typename T, int ... S >
		auto call_(const T & t, seq< S... >) const -> decltype(f(get< S >(t)...)) {
			return f(get< S >(t)...);
		}

	public:
		FunctionBinder(const F & f):
			f(f) { }

		template < typename ... Args >
		auto operator()(Args ... args) const -> decltype(f(declval< Args >()...)) {
			return f(args...);
		}

		template < typename ... Args >
		auto operator()(tuple< Args ... > t) const -> decltype(f(declval< Args >()...)) {
			return call_(t, typename gens< sizeof...(Args) >::type());
		}
	};

	template < typename F >
	const FunctionBinder< F > bindFunction(const F & f) {
		return FunctionBinder< F >(f);
	}

	template < typename F >
	const FunctionBinder< F > bind(const F & f) {
		return FunctionBinder< F >(f);
	}

	template < typename M >
	struct MethodBinder {
	protected:
		const M & m;

		template < typename O, typename T, int ... S >
		auto call_(const O & o, const T & t, seq< S... >) const -> decltype((const_cast< O & >(o).*m)(get< S >(t)...)) {
			return (const_cast< O & >(o).*m)(get< S >(t)...);
		}

	public:
		MethodBinder(const M & m):
			m(m) { }

		template < typename O, typename ... Args >
		auto operator()(const O & o, Args ... args) const -> decltype((const_cast< O & >(o).*m)(declval< Args >()...)) {
			return (const_cast< O & >(o).*m)(args...);
		}

		template < typename O, typename ... Args >
		auto operator()(const O & o, tuple< Args ... > t) const -> decltype((const_cast< O & >(o).*m)(declval< Args >()...)) {
			return call_(o, t, typename gens< sizeof...(Args) >::type());
		}
	};

	template < typename M >
	const MethodBinder< M > bindMethod(const M & m) {
		return MethodBinder< M >(m);
	}
}
#endif
