// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file HelloWorldOne.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_HELLOWORLDONE_H_
#define _FAST_DDS_GENERATED_HELLOWORLDONE_H_


#include <fastrtps/utils/fixed_size_string.hpp>

#include <stdint.h>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define eProsima_user_DllExport
#endif  // _WIN32

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(HelloWorldOne_SOURCE)
#define HelloWorldOne_DllAPI __declspec( dllexport )
#else
#define HelloWorldOne_DllAPI __declspec( dllimport )
#endif // HelloWorldOne_SOURCE
#else
#define HelloWorldOne_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define HelloWorldOne_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure HelloWorldOne defined by the user in the IDL file.
 * @ingroup HELLOWORLDONE
 */
class HelloWorldOne
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport HelloWorldOne();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~HelloWorldOne();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object HelloWorldOne that will be copied.
     */
    eProsima_user_DllExport HelloWorldOne(
            const HelloWorldOne& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object HelloWorldOne that will be copied.
     */
    eProsima_user_DllExport HelloWorldOne(
            HelloWorldOne&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object HelloWorldOne that will be copied.
     */
    eProsima_user_DllExport HelloWorldOne& operator =(
            const HelloWorldOne& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object HelloWorldOne that will be copied.
     */
    eProsima_user_DllExport HelloWorldOne& operator =(
            HelloWorldOne&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x HelloWorldOne object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const HelloWorldOne& x) const;

    /*!
     * @brief Comparison operator.
     * @param x HelloWorldOne object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const HelloWorldOne& x) const;

    /*!
     * @brief This function sets a value in member id
     * @param _id New value for member id
     */
    eProsima_user_DllExport void id(
            uint32_t _id);

    /*!
     * @brief This function returns the value of member id
     * @return Value of member id
     */
    eProsima_user_DllExport uint32_t id() const;

    /*!
     * @brief This function returns a reference to member id
     * @return Reference to member id
     */
    eProsima_user_DllExport uint32_t& id();

    /*!
     * @brief This function sets a value in member type
     * @param _type New value for member type
     */
    eProsima_user_DllExport void type(
            uint32_t _type);

    /*!
     * @brief This function returns the value of member type
     * @return Value of member type
     */
    eProsima_user_DllExport uint32_t type() const;

    /*!
     * @brief This function returns a reference to member type
     * @return Reference to member type
     */
    eProsima_user_DllExport uint32_t& type();

    /*!
     * @brief This function sets a value in member subtype
     * @param _subtype New value for member subtype
     */
    eProsima_user_DllExport void subtype(
            uint32_t _subtype);

    /*!
     * @brief This function returns the value of member subtype
     * @return Value of member subtype
     */
    eProsima_user_DllExport uint32_t subtype() const;

    /*!
     * @brief This function returns a reference to member subtype
     * @return Reference to member subtype
     */
    eProsima_user_DllExport uint32_t& subtype();

    /*!
     * @brief This function copies the value in member message
     * @param _message New value to be copied in member message
     */
    eProsima_user_DllExport void message(
            const std::string& _message);

    /*!
     * @brief This function moves the value in member message
     * @param _message New value to be moved in member message
     */
    eProsima_user_DllExport void message(
            std::string&& _message);

    /*!
     * @brief This function returns a constant reference to member message
     * @return Constant reference to member message
     */
    eProsima_user_DllExport const std::string& message() const;

    /*!
     * @brief This function returns a reference to member message
     * @return Reference to member message
     */
    eProsima_user_DllExport std::string& message();

    /*!
    * @brief This function returns the maximum serialized size of an object
    * depending on the buffer alignment.
    * @param current_alignment Buffer alignment.
    * @return Maximum serialized size.
    */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function returns the serialized size of a data depending on the buffer alignment.
     * @param data Data which is calculated its serialized size.
     * @param current_alignment Buffer alignment.
     * @return Serialized size.
     */
    eProsima_user_DllExport static size_t getCdrSerializedSize(
            const HelloWorldOne& data,
            size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(
            eprosima::fastcdr::Cdr& cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(
            eprosima::fastcdr::Cdr& cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(
            size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(
            eprosima::fastcdr::Cdr& cdr) const;

private:

    uint32_t m_id;
    uint32_t m_type;
    uint32_t m_subtype;
    std::string m_message;

};

#endif // _FAST_DDS_GENERATED_HELLOWORLDONE_H_