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
 * @file CPcSrcData.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _FAST_DDS_GENERATED_CPCSRCDATA_H_
#define _FAST_DDS_GENERATED_CPCSRCDATA_H_

#include "CDataBase.h"

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
#if defined(CPcSrcData_SOURCE)
#define CPcSrcData_DllAPI __declspec( dllexport )
#else
#define CPcSrcData_DllAPI __declspec( dllimport )
#endif // CPcSrcData_SOURCE
#else
#define CPcSrcData_DllAPI
#endif  // EPROSIMA_USER_DLL_EXPORT
#else
#define CPcSrcData_DllAPI
#endif // _WIN32

namespace eprosima {
namespace fastcdr {
class Cdr;
} // namespace fastcdr
} // namespace eprosima


/*!
 * @brief This class represents the structure CPcPoint defined by the user in the IDL file.
 * @ingroup CPCSRCDATA
 */
class CPcPoint
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport CPcPoint();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~CPcPoint();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object CPcPoint that will be copied.
     */
    eProsima_user_DllExport CPcPoint(
            const CPcPoint& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object CPcPoint that will be copied.
     */
    eProsima_user_DllExport CPcPoint(
            CPcPoint&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object CPcPoint that will be copied.
     */
    eProsima_user_DllExport CPcPoint& operator =(
            const CPcPoint& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object CPcPoint that will be copied.
     */
    eProsima_user_DllExport CPcPoint& operator =(
            CPcPoint&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x CPcPoint object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const CPcPoint& x) const;

    /*!
     * @brief Comparison operator.
     * @param x CPcPoint object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const CPcPoint& x) const;

    /*!
     * @brief This function sets a value in member fX
     * @param _fX New value for member fX
     */
    eProsima_user_DllExport void fX(
            float _fX);

    /*!
     * @brief This function returns the value of member fX
     * @return Value of member fX
     */
    eProsima_user_DllExport float fX() const;

    /*!
     * @brief This function returns a reference to member fX
     * @return Reference to member fX
     */
    eProsima_user_DllExport float& fX();

    /*!
     * @brief This function sets a value in member fY
     * @param _fY New value for member fY
     */
    eProsima_user_DllExport void fY(
            float _fY);

    /*!
     * @brief This function returns the value of member fY
     * @return Value of member fY
     */
    eProsima_user_DllExport float fY() const;

    /*!
     * @brief This function returns a reference to member fY
     * @return Reference to member fY
     */
    eProsima_user_DllExport float& fY();

    /*!
     * @brief This function sets a value in member fZ
     * @param _fZ New value for member fZ
     */
    eProsima_user_DllExport void fZ(
            float _fZ);

    /*!
     * @brief This function returns the value of member fZ
     * @return Value of member fZ
     */
    eProsima_user_DllExport float fZ() const;

    /*!
     * @brief This function returns a reference to member fZ
     * @return Reference to member fZ
     */
    eProsima_user_DllExport float& fZ();

    /*!
     * @brief This function sets a value in member fIntensity
     * @param _fIntensity New value for member fIntensity
     */
    eProsima_user_DllExport void fIntensity(
            float _fIntensity);

    /*!
     * @brief This function returns the value of member fIntensity
     * @return Value of member fIntensity
     */
    eProsima_user_DllExport float fIntensity() const;

    /*!
     * @brief This function returns a reference to member fIntensity
     * @return Reference to member fIntensity
     */
    eProsima_user_DllExport float& fIntensity();

    /*!
     * @brief This function sets a value in member fConfidence
     * @param _fConfidence New value for member fConfidence
     */
    eProsima_user_DllExport void fConfidence(
            float _fConfidence);

    /*!
     * @brief This function returns the value of member fConfidence
     * @return Value of member fConfidence
     */
    eProsima_user_DllExport float fConfidence() const;

    /*!
     * @brief This function returns a reference to member fConfidence
     * @return Reference to member fConfidence
     */
    eProsima_user_DllExport float& fConfidence();


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
            const CPcPoint& data,
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

    float m_fX;
    float m_fY;
    float m_fZ;
    float m_fIntensity;
    float m_fConfidence;

};
/*!
 * @brief This class represents the structure CPcSrcData defined by the user in the IDL file.
 * @ingroup CPCSRCDATA
 */
class CPcSrcData : public CDataBase 
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport CPcSrcData();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~CPcSrcData();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object CPcSrcData that will be copied.
     */
    eProsima_user_DllExport CPcSrcData(
            const CPcSrcData& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object CPcSrcData that will be copied.
     */
    eProsima_user_DllExport CPcSrcData(
            CPcSrcData&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object CPcSrcData that will be copied.
     */
    eProsima_user_DllExport CPcSrcData& operator =(
            const CPcSrcData& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object CPcSrcData that will be copied.
     */
    eProsima_user_DllExport CPcSrcData& operator =(
            CPcSrcData&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcData object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const CPcSrcData& x) const;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcData object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const CPcSrcData& x) const;

    /*!
     * @brief This function sets a value in member ucLidarId
     * @param _ucLidarId New value for member ucLidarId
     */
    eProsima_user_DllExport void ucLidarId(
            uint8_t _ucLidarId);

    /*!
     * @brief This function returns the value of member ucLidarId
     * @return Value of member ucLidarId
     */
    eProsima_user_DllExport uint8_t ucLidarId() const;

    /*!
     * @brief This function returns a reference to member ucLidarId
     * @return Reference to member ucLidarId
     */
    eProsima_user_DllExport uint8_t& ucLidarId();

    /*!
     * @brief This function sets a value in member unPointNums
     * @param _unPointNums New value for member unPointNums
     */
    eProsima_user_DllExport void unPointNums(
            uint32_t _unPointNums);

    /*!
     * @brief This function returns the value of member unPointNums
     * @return Value of member unPointNums
     */
    eProsima_user_DllExport uint32_t unPointNums() const;

    /*!
     * @brief This function returns a reference to member unPointNums
     * @return Reference to member unPointNums
     */
    eProsima_user_DllExport uint32_t& unPointNums();

    /*!
     * @brief This function copies the value in member vecPoints
     * @param _vecPoints New value to be copied in member vecPoints
     */
    eProsima_user_DllExport void vecPoints(
            const std::vector<CPcPoint>& _vecPoints);

    /*!
     * @brief This function moves the value in member vecPoints
     * @param _vecPoints New value to be moved in member vecPoints
     */
    eProsima_user_DllExport void vecPoints(
            std::vector<CPcPoint>&& _vecPoints);

    /*!
     * @brief This function returns a constant reference to member vecPoints
     * @return Constant reference to member vecPoints
     */
    eProsima_user_DllExport const std::vector<CPcPoint>& vecPoints() const;

    /*!
     * @brief This function returns a reference to member vecPoints
     * @return Reference to member vecPoints
     */
    eProsima_user_DllExport std::vector<CPcPoint>& vecPoints();

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
            const CPcSrcData& data,
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

    uint8_t m_ucLidarId;
    uint32_t m_unPointNums;
    std::vector<CPcPoint> m_vecPoints;

};
/*!
 * @brief This class represents the structure CPcSrcDataTimeMatch defined by the user in the IDL file.
 * @ingroup CPCSRCDATA
 */
class CPcSrcDataTimeMatch : public CDataBase 
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport CPcSrcDataTimeMatch();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~CPcSrcDataTimeMatch();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object CPcSrcDataTimeMatch that will be copied.
     */
    eProsima_user_DllExport CPcSrcDataTimeMatch(
            const CPcSrcDataTimeMatch& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object CPcSrcDataTimeMatch that will be copied.
     */
    eProsima_user_DllExport CPcSrcDataTimeMatch(
            CPcSrcDataTimeMatch&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object CPcSrcDataTimeMatch that will be copied.
     */
    eProsima_user_DllExport CPcSrcDataTimeMatch& operator =(
            const CPcSrcDataTimeMatch& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object CPcSrcDataTimeMatch that will be copied.
     */
    eProsima_user_DllExport CPcSrcDataTimeMatch& operator =(
            CPcSrcDataTimeMatch&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcDataTimeMatch object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const CPcSrcDataTimeMatch& x) const;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcDataTimeMatch object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const CPcSrcDataTimeMatch& x) const;

    /*!
     * @brief This function sets a value in member ucLidarId1
     * @param _ucLidarId1 New value for member ucLidarId1
     */
    eProsima_user_DllExport void ucLidarId1(
            uint8_t _ucLidarId1);

    /*!
     * @brief This function returns the value of member ucLidarId1
     * @return Value of member ucLidarId1
     */
    eProsima_user_DllExport uint8_t ucLidarId1() const;

    /*!
     * @brief This function returns a reference to member ucLidarId1
     * @return Reference to member ucLidarId1
     */
    eProsima_user_DllExport uint8_t& ucLidarId1();

    /*!
     * @brief This function copies the value in member vecSrcData
     * @param _vecSrcData New value to be copied in member vecSrcData
     */
    eProsima_user_DllExport void vecSrcData(
            const std::vector<CPcSrcData>& _vecSrcData);

    /*!
     * @brief This function moves the value in member vecSrcData
     * @param _vecSrcData New value to be moved in member vecSrcData
     */
    eProsima_user_DllExport void vecSrcData(
            std::vector<CPcSrcData>&& _vecSrcData);

    /*!
     * @brief This function returns a constant reference to member vecSrcData
     * @return Constant reference to member vecSrcData
     */
    eProsima_user_DllExport const std::vector<CPcSrcData>& vecSrcData() const;

    /*!
     * @brief This function returns a reference to member vecSrcData
     * @return Reference to member vecSrcData
     */
    eProsima_user_DllExport std::vector<CPcSrcData>& vecSrcData();

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
            const CPcSrcDataTimeMatch& data,
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

    uint8_t m_ucLidarId1;
    std::vector<CPcSrcData> m_vecSrcData;

};
/*!
 * @brief This class represents the structure CPcSrcPacketData defined by the user in the IDL file.
 * @ingroup CPCSRCDATA
 */
class CPcSrcPacketData : public CDataBase 
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport CPcSrcPacketData();

    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~CPcSrcPacketData();

    /*!
     * @brief Copy constructor.
     * @param x Reference to the object CPcSrcPacketData that will be copied.
     */
    eProsima_user_DllExport CPcSrcPacketData(
            const CPcSrcPacketData& x);

    /*!
     * @brief Move constructor.
     * @param x Reference to the object CPcSrcPacketData that will be copied.
     */
    eProsima_user_DllExport CPcSrcPacketData(
            CPcSrcPacketData&& x) noexcept;

    /*!
     * @brief Copy assignment.
     * @param x Reference to the object CPcSrcPacketData that will be copied.
     */
    eProsima_user_DllExport CPcSrcPacketData& operator =(
            const CPcSrcPacketData& x);

    /*!
     * @brief Move assignment.
     * @param x Reference to the object CPcSrcPacketData that will be copied.
     */
    eProsima_user_DllExport CPcSrcPacketData& operator =(
            CPcSrcPacketData&& x) noexcept;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcPacketData object to compare.
     */
    eProsima_user_DllExport bool operator ==(
            const CPcSrcPacketData& x) const;

    /*!
     * @brief Comparison operator.
     * @param x CPcSrcPacketData object to compare.
     */
    eProsima_user_DllExport bool operator !=(
            const CPcSrcPacketData& x) const;

    /*!
     * @brief This function copies the value in member vecPacketData
     * @param _vecPacketData New value to be copied in member vecPacketData
     */
    eProsima_user_DllExport void vecPacketData(
            const std::vector<std::string>& _vecPacketData);

    /*!
     * @brief This function moves the value in member vecPacketData
     * @param _vecPacketData New value to be moved in member vecPacketData
     */
    eProsima_user_DllExport void vecPacketData(
            std::vector<std::string>&& _vecPacketData);

    /*!
     * @brief This function returns a constant reference to member vecPacketData
     * @return Constant reference to member vecPacketData
     */
    eProsima_user_DllExport const std::vector<std::string>& vecPacketData() const;

    /*!
     * @brief This function returns a reference to member vecPacketData
     * @return Reference to member vecPacketData
     */
    eProsima_user_DllExport std::vector<std::string>& vecPacketData();

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
            const CPcSrcPacketData& data,
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

    std::vector<std::string> m_vecPacketData;

};

#endif // _FAST_DDS_GENERATED_CPCSRCDATA_H_