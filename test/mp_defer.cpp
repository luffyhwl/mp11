
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <type_traits>

template<class T> struct has_type
{
    template<class U> static boost::mp_true f( boost::mp_identity<typename U::type>* );
    template<class U> static boost::mp_false f( ... );

    using type = decltype( f<T>(0) );

    static const auto value = type::value;
};

using boost::mp_defer;

template<class T> using add_pointer = T*;
template<class... T> using add_pointer_impl = mp_defer<add_pointer, T...>;

int main()
{
    BOOST_TEST_TRAIT_TRUE((has_type<add_pointer_impl<void>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<add_pointer_impl<void>::type, void*>));

    BOOST_TEST_TRAIT_TRUE((has_type<add_pointer_impl<int>>));
    BOOST_TEST_TRAIT_TRUE((std::is_same<add_pointer_impl<int>::type, int*>));

    BOOST_TEST_TRAIT_FALSE((has_type<add_pointer_impl<>>));
    BOOST_TEST_TRAIT_FALSE((has_type<add_pointer_impl<void, void>>));

    return boost::report_errors();
}
