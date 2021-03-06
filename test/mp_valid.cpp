
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt


#include <boost/mp11/utility.hpp>
#include <boost/core/lightweight_test_trait.hpp>

template<class T> struct Xi
{
};

template<> struct Xi<void>
{
    using type = void;
};

template<class T> using X = typename Xi<T>::type;

template<class T> using add_pointer = T*;
template<class T> using add_reference = T&;
template<class T> using add_extents = T[];

int main()
{
    using boost::mp_valid;
    using boost::mp_identity;

    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_identity>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<mp_identity, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<mp_identity, void, void>));

    BOOST_TEST_TRAIT_FALSE((mp_valid<X>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<X, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<X, int>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<X, void, void>));

    BOOST_TEST_TRAIT_FALSE((mp_valid<add_pointer>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<add_pointer, void>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<add_pointer, int>));
#if !defined( BOOST_MSVC ) || !BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )
    // msvc-12.0 can form pointer to reference
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_pointer, int&>));
#endif
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_pointer, void, void>));

#if !defined( BOOST_GCC ) || !BOOST_WORKAROUND( BOOST_GCC, <= 40902 )
    // g++ 4.9.2 doesn't like add_reference for some reason or other
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_reference>));
#if !defined( BOOST_MSVC ) || !BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )
    // msvc-12.0 gives an internal error here
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_reference, void>));
#endif
    BOOST_TEST_TRAIT_TRUE((mp_valid<add_reference, int>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_reference, int, int>));
#endif

    BOOST_TEST_TRAIT_FALSE((mp_valid<add_extents>));
    BOOST_TEST_TRAIT_TRUE((mp_valid<add_extents, int>));
#if !defined( BOOST_MSVC ) || !BOOST_WORKAROUND( BOOST_MSVC, <= 1800 )
    // msvc-12.0 can form arrays to void or int&
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_extents, void>));
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_extents, int&>));
#endif
    BOOST_TEST_TRAIT_FALSE((mp_valid<add_extents, int, int>));

    return boost::report_errors();
}
