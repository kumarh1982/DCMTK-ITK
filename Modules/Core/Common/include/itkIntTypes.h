/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkIntTypes_h
#define __itkIntTypes_h

#include "itkConfigure.h"

#if defined( ITK_HAVE_STDINT_H )
#include <stdint.h>
#else
// the system doesn't have the C or C++ version of stdint so lets use
// itksys's types for fixed widths
#include "itksys/FundamentalType.h"

#ifdef ITK_HAVE_STDDEF_H
#include <stddef.h>
#endif //ITK_HAVE_STDDEF_H

#endif // ITK_HAVE_CSTDINT

#include <limits.h>

namespace itk
{
#if defined( ITK_HAVE_STDINT_H )

// Note: these types are technically optional in C99 stdint.h file. As
// such a try complile for their existance may be needed.
typedef::int8_t   int8_t;
typedef::uint8_t  uint8_t;
typedef::int16_t  int16_t;
typedef::uint16_t uint16_t;
typedef::int32_t  int32_t;
typedef::uint32_t uint32_t;
typedef::int64_t  int64_t;
typedef::uint64_t uint64_t;

// Note: these types are required for the C99 stdint.h file.
typedef::int_least8_t   int_least8_t;
typedef::uint_least8_t  uint_least8_t;
typedef::int_least16_t  int_least16_t;
typedef::uint_least16_t uint_least16_t;
typedef::int_least32_t  int_least32_t;
typedef::uint_least32_t uint_least32_t;
typedef::int_least64_t  int_least64_t;
typedef::uint_least64_t uint_least64_t;

// Note: these types are required for the C99 stdint.h file.
typedef::int_fast8_t   int_fast8_t;
typedef::uint_fast8_t  uint_fast8_t;
typedef::int_fast16_t  int_fast16_t;
typedef::uint_fast16_t uint_fast16_t;
typedef::int_fast32_t  int_fast32_t;
typedef::uint_fast32_t uint_fast32_t;
typedef::int_fast64_t  int_fast64_t;
typedef::uint_fast64_t uint_fast64_t;

typedef::intmax_t  intmax_t;
typedef::uintmax_t uintmax_t;

typedef::intptr_t  intptr_t;
typedef::uintptr_t uintptr_t;

#else // ITK_HAVE_STDINT_H

/** Fixed width interger types. */
typedef::itksysFundamentalType_Int8   int8_t;
typedef::itksysFundamentalType_UInt8  uint8_t;
typedef::itksysFundamentalType_Int16  int16_t;
typedef::itksysFundamentalType_UInt16 uint16_t;
typedef::itksysFundamentalType_Int32  int32_t;
typedef::itksysFundamentalType_UInt32 uint32_t;
typedef::itksysFundamentalType_Int64  int64_t;
typedef::itksysFundamentalType_UInt64 uint64_t;

/** Types which are at least a certain size, these are prefered over
 *  fixed width. */
typedef int8_t   int_least8_t;
typedef uint8_t  uint_least8_t;
typedef int16_t  int_least16_t;
typedef uint16_t uint_least16_t;
typedef int32_t  int_least32_t;
typedef uint32_t uint_least32_t;
typedef int64_t  int_least64_t;
typedef uint64_t uint_least64_t;

/** Types which are at least a certain size but may be greater if
 *  performace benifits, these are prefered over fixed width. */
typedef int8_t   int_fast8_t;
typedef uint8_t  uint_fast8_t;
typedef int16_t  int_fast16_t;
typedef uint16_t uint_fast16_t;
typedef int32_t  int_fast32_t;
typedef uint32_t uint_fast32_t;
typedef int64_t  int_fast64_t;
typedef uint64_t uint_fast64_t;

/** Types which contain the largest represetable integer. */
typedef int64_t  intmax_t;
typedef uint64_t uintmax_t;

typedef::ptrdiff_t intptr_t;
typedef::size_t    uintptr_t;

#endif // ITK_HAVE_STDINT_H

#if !defined(ITKV3_COMPATIBILITY) && defined(ITK_USE_64BITS_IDS) && ((ULLONG_MAX != ULONG_MAX) || (LLONG_MAX != LONG_MAX))

/** Any count of number of items (number of pixels in an image, number of
 *  points) (it is unsigned) */
typedef uint64_t      SizeValueType;

/** Same type as SizeValueType but when used as an Id (pointId, cellId,
 *  labelObjectId..)(it is unsigned) */
typedef SizeValueType IdentifierType;

/** The components of the Index array (they are signed) */
typedef int64_t       IndexValueType;

/** Differences between components of indexes, distance from one pointer
 *  to the origin of a buffer (it is signed) */
typedef int64_t       OffsetValueType;

#else

/** Any count of number of items (number of pixels in an image, number of
 *  points) (it is unsigned) */
typedef unsigned long     SizeValueType;

/** Same type as SizeValueType but when used as an Id (pointId, cellId,
 *  labelObjectId..)(it is unsigned) */
typedef SizeValueType IdentifierType;

/** The components of the Index array (they are signed) */
typedef signed long   IndexValueType;

/** Differences between components of indexes, distance from one pointer
 *  to the origin of a buffer (it is signed) */
typedef signed long   OffsetValueType;

#endif

/** Type to count and reference number of threads */
typedef unsigned int  ThreadIdType;

}

#endif  /* __itkIntTypes_h */
