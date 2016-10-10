#pragma once

#include <endian.h>
#include <byteswap.h>
#include <stdint.h>
#include <stddef.h>

#include <binary.hpp>

namespace kb {
  namespace binary {
    namespace byteorder {

      // 
      // Swap - swap byte order
      // 

      template <typename T, size_t byte>
      struct Swaper;

      template <typename T>
      inline
      T Swap(T value) {
        return Swaper<T, sizeof(T)>::Swap(value);
      }

      template <typename T, size_t byte>
      struct Swaper
      {
        typedef typename T::__not_supported_type__ type;
        static T Swap(T n);
      };

      // Implementation:
      // use bswap_xx to optimize, but may only supported by linux

      template <typename T>
      struct Swaper<T, 1>
      {
        static T Swap(T n) {
          return n;
        }
      };

      template <typename T>
      struct Swaper<T, 2>
      {
        static T Swap(T n) {
          return bswap_16(n);
        }
      };

      template <typename T>
      struct Swaper<T, 4>
      {
        static T Swap(T n) {
          return bswap_32(n);
        }
      };

      template <typename T>
      struct Swaper<T, 8>
      {
        static T Swap(T n) {
          return bswap_64(n);
        }
      };


      //
      // Cast - case byte order
      // 

      template <typename from, typename to>
      struct Caster;

      template <typename FromOrder,
                typename ToOrder,
                typename T>
      inline
      T Cast(T value) {
        return Caster<FromOrder, ToOrder>::cast(value);
      }

      template <typename Order,
                typename T>
      inline
      T CastFrom(T value) {
        return Cast<Order, Host, T>(value);
      }

      template <typename Order,
                typename T>
      inline
      T CastTo(T value) {
        return Cast<Host, Order, T>(value);
      }

      template <typename T>
      inline
      T Ntoh(T value) {
        return Cast<Network, Host, T>(value);
      }

      template <typename T>
      inline
      T Hton(T value) {
        return Cast<Host, Network, T>(value);
      }

      template <typename from, typename to>
      struct Caster {
        template <typename T>
        static inline
        T cast(T n) {
          // for different byte order
          return Swap(n);
        }
      };

      // specialization for same byte order
      template <typename order>
      struct Caster<order, order> {
        template <typename T>
        static inline
        T cast(T n) {
          return n;
        }
      };

    } // byteorder
  } // binary
}
