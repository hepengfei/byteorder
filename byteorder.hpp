// -*-mode:c++; coding:utf-8-*-

#ifndef _KB_BYTEORDER_HPP_
#define _KB_BYTEORDER_HPP_

//
// about endianess, please see
// http://www.cs.umass.edu/~verts/cs32/endian.html
// 

#include <endian.h>
#include <byteswap.h>
#include <stdint.h>
#include <stddef.h>

namespace kb
{

	//
	// byteorder types
	//

	struct little_endian {};
	struct big_endian {};

	// alias

	// network using big endian byteorder
	typedef big_endian network_byteorder;

#if __BYTE_ORDER == __LITTLE_ENDIAN
	typedef little_endian host_byteorder;
#else
	typedef big_endian host_byteorder;
#endif

	namespace details
	{
		// use bswap_xx to optimize, but may only supported by
		// linux

		template<typename T, size_t byte>
		struct byte_swap_helper
		{
			typedef typename T::__not_supported_type__ type;
			static T swap(T n);
		};

		template<typename T>
		struct byte_swap_helper<T, 1>
		{
			static T swap(T n) {
				return n;
			}
		};

		template<typename T>
		struct byte_swap_helper<T, 2>
		{
			static T swap(T n) {
				return bswap_16(n);
			}
		};

		template<typename T>
		struct byte_swap_helper<T, 4>
		{
			static T swap(T n) {
				return bswap_32(n);
			}
		};

		template<typename T>
		struct byte_swap_helper<T, 8>
		{
			static T swap(T n) {
				return bswap_64(n);
			}
		};

	} // namespace details

	//
	// swap_byteorder - swap byteorder from one to another
	//
	
	template<typename Integer>
	inline
	Integer swap_byteorder(Integer n) {
		return details::byte_swap_helper<Integer, sizeof(Integer)>::swap(n);
	}

	namespace details
	{

		//
		// byteorder_cast_helper - the helper class for byteorder_cast
		// 

		template<typename from, typename to>
		struct byteorder_cast_helper { // for different byteorder
			template<typename Integer>
			static inline
			Integer cast(Integer n) {
				return swap_byteorder(n);
			}
		};

		template<typename order> // the same byteorder version
		struct byteorder_cast_helper<order, order> {
			template<typename Integer>
			static inline
			Integer cast(Integer n) {
				return n;
			}
		};

	} // namespace details

	//
	// byteorder_cast - provide a cast type operator
	//
	// int n; 
	// byteorder_cast<host_byteorder, network_byteorder>(n);
	// 

	template<typename from,
		 typename to,
		 typename Integer>
	inline
	Integer byteorder_cast(Integer n) {
		return details::byteorder_cast_helper<from, to>::cast(n);
	}
	
	//
	// from_order, to_order - swap between order with host_order
	//

	template<typename order,
		 typename Integer>
	inline
	Integer from_byteorder_cast(Integer n) {
		return byteorder_cast<order, host_byteorder, Integer>(n);
	}

	template<typename order,
		 typename Integer>
	inline
	Integer to_byteorder_cast(Integer n) {
		return byteorder_cast<host_byteorder, order, Integer>(n);
	}

	//
	// ntoh, hton - the famous system function
	// 

	template<typename Integer>
	inline
	Integer ntoh(Integer n) {
		return byteorder_cast<network_byteorder, host_byteorder>(n);
	}

	template<typename Integer>
	inline
	Integer hton(Integer n) {
		return byteorder_cast<host_byteorder, network_byteorder>(n);
	}

	//
	// is_little_endian - true if given little_endian
	//

	template<typename byteorder>
	struct is_little_endian {
		static const bool value = false;
	};

	template<>
	struct is_little_endian<little_endian> {
		static const bool value = true;
	};

	//
	// is_big_endian - true if given big_endian
	//

	template<typename byteorder>
	struct is_big_endian {
		static const bool value = false;
	};

	template<>
	struct is_little_endian<big_endian> {
		static const bool value = true;
	};

	//
	// reversed_byteorder - return the reversed byteorder
	//
	
	template<typename byteorder>
	struct reversed_byteorder;

	template<>
	struct reversed_byteorder<little_endian> {
		typedef big_endian type;
	};

	template<>
	struct reversed_byteorder<big_endian> {
		typedef little_endian type;
	};

	//
	// is_same_byteorder
	// 

	template<typename byteorder1,
		 typename byteorder2>
	struct is_same_byteorder;

	template<typename byteorder>
	struct is_same_byteorder<byteorder, byteorder> {
		static const bool value = true;
	};

	template<typename byteorder>
	struct is_same_byteorder<byteorder,
				 typename reversed_byteorder<byteorder>::type> {
		static const bool value = false;
	};

} // namespace kb

#endif	// _KB_BYTEORDER_HPP_
