/**
 * @file    Bfx_64bits.h
 * @brief   **Specification of 64 Bit Handling Routines**
 *
 * AUTOSAR Library routines are the part of system services in AUTOSAR architecture and below figure
 * shows position of AUTOSAR library in layered architecture.
 *
 * Bfx routines specification specifies the functionality, API and the configuration of the AUTOSAR
 * library for BIT functionality dedicated to fixed-point arithmetic routines All bit functions are
 * re-entrant and can handle several simultaneous requests from the application.
 *
 * @reqs    SWS_Bfx_00223, SWS_Bfx_00203, SWS_Bfx_00205, SWS_Bfx_00206, SWS_Bfx_00207, SWS_Bfx_00208
 *          SWS_Bfx_00209, SWS_Bfx_00212, SWS_Bfx_00213, SWS_Bfx_00214,
 */
#ifndef BFX_64BITS_H
#define BFX_64BITS_H

#include "Std_Types.h"

/**
 * @brief **64 bits Set Bit**
 *
 * Sets the logical status of an 64 bits input data as 1 at the requested bit postion.
 *
 * **Example:**
 *      @code
 *      Data = 10001010b
 *      Bfx_SetBit_u64u8(&Data, 2);
 *      The Data will be updated to 10001110b
 *      @endcode
 *
 * @param[inout]  Data Pointer to input data
 * @param[in]  BitPn Bit position
 *
 * @reqs    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void Bfx_SetBit_u64u8( uint64 *Data, uint8 BitPn )
{
    *Data |= ( 1u << BitPn );
}

/**
 * @brief **64 bits Clear Bit**
 *
 * Clears the logical status of an 64 bit input data as 0 at the requested bit postion.
 *
 * **Example:**
 *      @code
 *      Data = 10001010b
 *      Bfx_ClrBit_u64u8(&Data, 1);
 *      The Data will be updated to 10001000b
 *      @endcode
 *
 * @param[inout]  Data Pointer to inpur data
 * @param[in]  BitPn Bit position
 *
 * @reqs    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void Bfx_ClrBit_u64u8( uint64 *Data, uint8 BitPn )
{
    *Data &= ~( 1u << BitPn );
}

/**
 * @brief **64 bits Get Bit**
 *
 * Returns the logical status of the 64 bit input data for the requested bit position.
 *
 * **Example:**
 *      @code
 *      Bit = Bfx_GetBit_u64u8(10001010b, 1);
 *      Bit will be equal to TRUE
 *      @endcode
 *
 * @param[in] Data Input data
 * @param[in] BitPn Bit position
 *
 * @retval Boolean Bit status
 *
 * @reqs    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
boolean Bfx_GetBit_u64u8_u8( uint64 Data, uint8 BitPn )
{
    return ( ( Data & ( 1u << BitPn ) ) != 0u );
}

/**
 * @brief **64 bits Write Multiple Bits**
 *
 * Sets the input data as 1 or 0 as per Status value starting from BitStartPn for the length BitLn.
 *
 * **Example:**
 *      @code
 *      Data = 00000111b
 *      Bfx_SetBits_u64u8u8u8(&Data, 4, 3, 1);
 *      The Data will be updated to 11110111b
 *      @endcode
 *
 * @param[inout]  Data Pointer to input Data
 * @param[in]  BitStartPn Start bit position
 * @param[in]  BitLn Bit field length
 * @param[in]  Status Status value
 *
 * @reqs    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void Bfx_SetBits_u64u8u8u8( uint64 *Data, uint8 BitStartPn, uint8 BitLn, uint8 Status )
{
    uint64 Mask;

    Mask = 0xFFFFFFFFu << BitStartPn;
    Mask &= ~( 0xFFFFFFFFu << ( BitStartPn + BitLn ) );

    if( Status == TRUE )
    {
        *Data |= Mask;
    }
    else
    {
        *Data &= ~Mask;
    }
}

/**
 * @brief **64 bits Get Multiple Bits**
 *
 * Returns the Bits of the input data starting from BitStartPn for the length of BitLn.
 *
 * **Example:**
 *      @code
 *      Data = Bfx_GetBits_u64u8u8_u64(01100111b, 4, 3)
 *      data will be equal to 00000110b
 *      @endcode
 *
 * @param[in]  Data Input Data
 * @param[in]  BitStartPn Start bit position
 * @param[in]  BitLn Bit field length
 *
 * @retval uint8 Bit field sequence
 *
 * @reqs    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
uint64 Bfx_GetBits_u64u8u8_u64( uint64 Data, uint8 BitStartPn, uint8 BitLn )
{
    uint64 Bits;

    Bits = Data >> BitStartPn;
    Bits &= ~( 0xFFFFFFFFFFFFFFFFu << ( BitLn ) );

    return Bits;
}

/**
 * @brief **64 bits Set Multiple Bits**
 *
 * Set the data to logical status '1' as per the corresponding Mask bits when set to value 1 and
 * remaining bits will retain their original values.
 *
 * **Example:**
 *      @code
 *      Data = 01100111b
 *      SetBitMask_u64u64(&Data, 11110000b)
 *      Data will be equal to 11110111b
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] Mask Mask used to set bits
 *
 * @reqs    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void Bfx_SetBitMask_u64u64( uint64 *Data, uint64 Mask )
{
    *Data |= Mask;
}

/**
 * @brief  **64 bits Clear Multiple Bits**
 *
 * Clears the data to logical status 0 as per the corresponding mask bits value when set to 1.The
 * remaining bits shall retain their original values.
 *
 * **Example:**
 *      @code
 *      Data = 01100111b
 *      Bfx_ClrBitMask_u64u64(&Data, 11110000b)
 *      Data will be equal to 00000111b
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] Mask Mask value
 *
 * @reqs    SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045
 */
void Bfx_ClrBitMask_u64u64( uint64 *Data, uint64 Mask )
{
    *Data &= ~Mask;
}

/**
 * @brief  **64 bit Test mask values**
 *
 * Returns 1 if all bits defined in Mask value are set in the input Data value. In all other cases
 * this function shall return 0.
 *
 * **Example:**
 *      @code
 *      Res = Bfx_TstBitMask_u64u64_u8(10010011b,10010000b)
 *      Res will equal to TRUE.
 *      @endcode
 *
 * @param[in] Data Input Data
 * @param[in] Mask Mask value
 *
 * @retval Boolean Value
 *
 * @reqs    SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
boolean Bfx_TstBitMask_u64u64_u8( uint64 Data, uint64 Mask )
{
    return ( ( Data & Mask ) == Mask );
}

/**
 * @brief **64 bit test at least one bit set**
 *
 * Makes a test on the input data and if at least one bit is set as per the mask, then the function
 * shall return TRUE, otherwise it shall return FALSE.
 *
 * **Example:**
 *      @code
 *      Res = Bfx_TstBitLnMask_u64u64_u8(10010011b,00010000b)
 *      Res will equal to TRUE.
 *      @endcode
 *
 * @param[in] Data Input Data
 * @param[in] Mask Mask value
 *
 * @retval Boolean Value
 *
 * @reqs    SWS_Bfx_00051, SWS_Bfx_00055
 */
boolean Bfx_TstBitLnMask_u64u64_u8( uint64 Data, uint64 Mask )
{
    return ( ( Data & Mask ) != 0u );
}

/**
 * @brief **64 bit test parity**
 *
 * Tests the number of bits set to 1. If this number is even, it shall return TRUE, otherwise it
 * returns FALSE.
 *
 * **Example:**
 *      @code
 *      Res = Bfx_TstParityEven_u64_u8(01010000b)
 *      Res will equal to TRUE.
 *      @endcode
 *
 * @param[in] Data Input Data
 *
 * @retval Boolean Value
 *
 * @reqs    SWS_Bfx_00056, SWS_Bfx_00060
 */
boolean Bfx_TstParityEven_u64_u8( uint64 Data )
{
    uint8 Count = 0u;
    uint64 Temp = Data;

    while( Temp != 0u )
    {
        Count += ( Temp & 1u );
        Temp >>= 1u;
    }

    return ( Count % 2u ) == 0u;
}

/**
 * @brief  **64 bit Toggle bits**
 *
 * Toggles all the bits of data (1's Complement Data).
 *
 * **Example:**
 *      @code
 *      Data = 01010001b
 *      Bfx_ToggleBits_u64(&Data)
 *      Data will equal to 10101110b.
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 *
 * @reqs    SWS_Bfx_00061, SWS_Bfx_00065
 */
void Bfx_ToggleBits_u64( uint64 *Data )
{
    *Data ^= 0xFFFFFFFFFFFFFFFFu;
}

/**
 * @brief **64 bit Toggle multiple bits**
 *
 * This function toggles the bits of data when the corresponding bit of the mask is enabled and set to 1.
 *
 * **Example:**
 *      @code
 *      Data = 01010001b
 *      Bfx_ToggleBitMask_u64u64(&Data, 11000011b)
 *      Data will equal to 10010010b.
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] Mask Mask
 *
 * @reqs    SWS_Bfx_00066, SWS_Bfx_00069
 */
void Bfx_ToggleBitMask_u64u64( uint64 *Data, uint64 Mask )
{
    *Data ^= Mask;
}

/**
 * @brief  **64 bit Shift to the right**
 *
 * This function shall shift data to the right by ShiftCnt. The most significant bit (left-most bit) is
 * replaced by a ’0’ bit and the least significant bit (right-most bit) is discarded for every single bit
 * shift cycle.
 *
 * **Example:**
 *      @code
 *      Data = 01010001b
 *      Bfx_ShiftBitRt_u64u8(&Data, 3)
 *      Data will equal to 00001010b.
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] ShiftCnt Shift right count
 *
 * @reqs    SWS_Bfx_00070, SWS_Bfx_00075
 */
void Bfx_ShiftBitRt_u64u8( uint64 *Data, uint8 ShiftCnt )
{
    *Data >>= ShiftCnt;
}

/**
 * @brief  **64 bit Shift to the left**
 *
 * This function shall shift data to the left by ShiftCnt. The least significant bit (right-most bit) is
 * replaced by a ’0’ bit and the most significant bit (left-most bit) is discarded for every single bit
 * shift cycle.
 *
 * **Example:**
 *      @code
 *      Data = 01010001b
 *      Bfx_ShiftBitLt_u64u8(&Data, 3)
 *      Data will equal to 10001000b.
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] ShiftCnt Shift left count
 *
 * @reqs    SWS_Bfx_00076, SWS_Bfx_00080
 */
void Bfx_ShiftBitLt_u64u8( uint64 *Data, uint8 ShiftCnt )
{
    *Data <<= ShiftCnt;
}

/**
 * @brief  **64 bit Rotate to the right**
 *
 * This function shall rotate data to the right by ShiftCnt. The least significant bit is rotated to the
 * most significant bit location for every single bit shift cycle.
 *
 * **Example:**
 *      @code
 *      If ShiftCnt = 1 then,
 *      uint64 Data = 0001 0111 (before rotate right)
 *      Data = 1000 1011 (after rotate right)
 *
 *      If ShiftCnt = 3 then,
 *      uint64 Data = 0001 0111 (before rotate right)
 *      Data = 1110 0010 (after rotate right)
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] ShiftCnt Shift right count
 *
 * @reqs    SWS_Bfx_00086, SWS_Bfx_00090
 */
void Bfx_RotBitRt_u64u8( uint64 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data << ( 64u - ShiftCnt ) ) | ( *Data >> ShiftCnt );
}

/**
 * @brief  **64 bit Rotate to the left**
 *
 * This function shall rotate data to the left by ShiftCnt. The most significant bit is rotated to the
 * least significant bit location for every single bit shift cycle
 *
 * **Example:**
 *      @code
 *      If ShiftCnt = 1 then,
 *      uint64 Data = 1011 0111 (before rotate left)
 *      Data = 0110 1111 (after rotate left)
 *
 *      If ShiftCnt = 3 then,
 *      uint64 Data = 1011 0111 (before rotate left)
 *      Data = 1011 1101 (after rotate left)
 *      @endcode
 *
 * @param[inout] Data Pointer to input Data
 * @param[in] ShiftCnt Shift left count
 *
 * @reqs    SWS_Bfx_00095, SWS_Bfx_00098
 */
void Bfx_RotBitLt_u64u8( uint64 *Data, uint8 ShiftCnt )
{
    *Data = ( *Data >> ( 64u - ShiftCnt ) ) | ( *Data << ShiftCnt );
}

/**
 * @brief  **64 bit Copy bits**
 *
 * This function shall copy a bit from source data from bit position to destination data at bit
 * position.
 *
 * **Example:**
 *      @code
 *      DestinationData = 10100001b
 *      BFX_CopyBit_u64u8u64u8(&DestinationData, 6, 11011010, 1)
 *      The DestinationData will have 11100001b
 *      @endcode
 *
 * @param[inout] DestinationData Pointer to destination data
 * @param[in] DestinationPosition Destination position
 * @param[in] SourceData Source data
 * @param[in] SourcePosition Source position
 *
 * @reqs    SWS_Bfx_00101, SWS_Bfx_00108
 */
void Bfx_CopyBit_u64u8u64u8( uint64 *DestinationData, uint8 DestinationPosition, uint64 SourceData, uint8 SourcePosition )
{
    if( ( SourceData & ( 1u << SourcePosition ) ) == 0u )
    {
        *DestinationData &= ~( 1u << DestinationPosition );
    }
    else
    {
        *DestinationData |= ( 1u << DestinationPosition );
    }
}

/**
 * @brief  **64 bit Put bitst**
 *
 * This function shall put bits as mentioned in Pattern to the input Data from the specified bit
 * position.
 *
 * **Example:**
 *      @code
 *      Data = 11110000b
 *      Bfx_PutBits_u64u8u8u64(&Data, 1, 3, 00000011b)
 *      The Data will have 11110110b
 *      @endcode
 *
 * @param[inout] Data Pointer to input data
 * @param[in] BitStartPn Start bit position
 * @param[in] BitLn Bit field length
 * @param[in] Pattern Pattern to be set
 *
 * @reqs    SWS_Bfx_00110, SWS_Bfx_00112
 */
void Bfx_PutBits_u64u8u8u64( uint64 *Data, uint8 BitStartPn, uint8 BitLn, uint64 Pattern )
{
    uint64 Mask = ( 1u << BitLn ) - 1u;

    *Data &= ~( Mask << BitStartPn );
    *Data |= ( Pattern & Mask ) << BitStartPn;
}

/**
 * @brief  **64 bit Put bitst**
 *
 * This function shall put bits as mentioned in Pattern to the input Data from the specified bit
 * position.
 *
 * **Example:**
 *      @code
 *      Data = 11100000b
 *      Bfx_PutBitsMask_u64u64u64(&Data, 11001101b, 00001111b)
 *      results in Data = 11101101b
 *      @endcode
 *
 * @param[inout] Data Pointer to input data
 * @param[in] Pattern Pattern to be set
 * @param[in] Mask Mask value
 *
 * @reqs    SWS_Bfx_00120, SWS_Bfx_00124
 */
void Bfx_PutBitsMask_u64u64u64( uint64 *Data, uint64 Pattern, uint64 Mask )
{
    *Data = ( ( Pattern & Mask ) | ( *Data & ~Mask ) );
}

/**
 * @brief  **64 bit Put single bit**
 *
 * This function shall update the bit specified by BitPn of input data as ’1’ or ’0’ as per ’Status’
 * value.
 *
 * **Example:**
 *      @code
 *      uint8 InputData = 11100111b;
 *      Bfx_PutBit_u64u8u8(&InputData, 4, TRUE);
 *      results in InputData = 11110111b
 *      @endcode
 *
 * @param[inout] Data Pointer to destination data
 * @param[in] BitPn Destination position
 * @param[in] Status Source data
 *
 * @reqs    SWS_Bfx_00130, SWS_Bfx_00132
 */
void Bfx_PutBit_u64u8u8( uint64 *Data, uint8 BitPn, boolean Status )
{
    if( Status == TRUE )
    {
        *Data |= ( 1u << BitPn );
    }
    else
    {
        *Data &= ~( 1u << BitPn );
    }
}

/**
 * @brief  **64 bit Arithmetic shift with saturation**
 *
 * For signed data an arithmetic shift is performed. The vacated bits are filled with zeros
 * and the result is saturated if its sign bit differs from the sign bits that are shifted out.
 *
 * If the shift count is less than zero, right-shift the value in Data by the absolute value of
 * the shift count. The vacated bits are filled with the sign-bit (the most significant bit) and
 * bits shifted out are discarded.
 *
 * Note that a shift right by the word width leaves all zeros or all ones in the result, de-
 * pending on the sign-bit.
 *
 * **Example:**
 *      @code
 *      a 64 bit signed integer: The range for shift count is -64 to +31, allowing a shift left
 *      up to 31 bit positions and a shift right up to 64 bit positions (a shift right by 64
 *      bits leaves all zeros or all ones in the result, depending on the sign bit)
 *      @endcode
 *
 * @param[in] ShiftCnt Shift count (-MaxShiftRight ... -1: right, 1 ... MaxShiftLeft:left)
 * @param[in] Data Input value
 *
 * @retval Shifted and saturated bit pattern.
 *
 * @reqs    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
static inline sint64 Bfx_ShiftBitSat_s64s8_s64( sint64 Data, sint8 ShiftCnt )
{
    sint64 result;

    if( ShiftCnt >= 0 )
    {
        result = Data << ShiftCnt; /*Shift left*/
        /*Check for saturation */
        if( ( ( Data < 0 ) && ( result > Data ) ) || ( ( Data >= 0 ) && ( result < Data ) ) )
        {
            if( Data < 0 )
            {
                result = INT64_MIN;
            }
            else
            {
                result = INT64_MAX;
            }
        }
    }
    else
    {
        result = Data >> ( -ShiftCnt ); /* Shift right */
        /* Fill vacated bits with the sign bit */
        if( Data < 0 )
        {
            result |= (sint64)( 0xFFFFFFFFFFFFFFFF << ( 64 + ShiftCnt ) );
        }
    }

    return result;
}

/**
 * @brief  **64 bit Arithmetic shift with saturation**
 *
 * For signed data an arithmetic shift is performed. The vacated bits are filled with zeros
 * and the result is saturated if its sign bit differs from the sign bits that are shifted out.
 *
 * If the shift count is less than zero, right-shift the value in Data by the absolute value of
 * the shift count. The vacated bits are filled with the sign-bit (the most significant bit) and
 * bits shifted out are discarded.
 *
 * Note that a shift right by the word width leaves all zeros or all ones in the result, de-
 * pending on the sign-bit.
 *
 * **Example:**
 *      @code
 *      a 64 bit signed integer: The range for shift count is -64 to +31, allowing a shift left
 *      up to 31 bit positions and a shift right up to 64 bit positions (a shift right by 64
 *      bits leaves all zeros or all ones in the result, depending on the sign bit)
 *      @endcode
 *
 * @param[in] ShiftCnt Shift count (-MaxShiftRight ... -1: right, 1 ... MaxShiftLeft:left)
 * @param[in] Data Input value
 *
 * @retval Shifted and saturated bit pattern.
 *
 * @reqs    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
static inline uint64 Bfx_ShiftBitSat_u64s8_u64( uint64 Data, sint8 ShiftCnt )
{
    uint64 result;

    if( ShiftCnt >= 0 )
    {
        result = Data << ShiftCnt; /*Shift left */
        /*Check for saturation */
        if( result < Data )
        {
            result = UINT64_MAX; /*Saturate result */
        }
    }
    else
    {
        result = Data >> ( -ShiftCnt );                            /* Shift right */
        result &= (uint64)( 0xFFFFFFFFFFFFFFFF >> ( -ShiftCnt ) ); /*Fill vacated bits with zero */
    }

    return result;
}

/**
 * @brief  **64 bit Count Leading Ones**
 *
 * Count the number of consecutive ones in Data starting with the most significant bit and return
 * the result.
 *
 * **Example:**
 *      @code
 *      Res = Bfx_CountLeadingOnes_u64(11100110b);
 *      Res is equal to 3
 *      @endcode
 *
 * @param[in] Data Input data
 *
 * @retval Bit position
 *
 * @reqs    SWS_Bfx_91003, SWS_Bfx_00137
 */
uint8 Bfx_CountLeadingOnes_u64( uint64 Data )
{
    uint8 Count       = 0u;
    uint64 BitChecker = 0x8000000000000000u;

    while( ( Data & BitChecker ) != 0u )
    {
        Count++;
        BitChecker >>= 1u;
    }

    return Count;
}

/**
 * @brief  **64 bit Count Leading bits**
 *
 * Count the number of consecutive bits which have the same value as most significant bit in Data,
 * starting with bit at position msb minus one. Put the result in Data. It is the number of leading
 * sign bits minus one, giving the number of redundant sign bits in Data
 *
 * **Example:**
 *      @code
 *      Res = Bfx_CountLeadingSigns_s64(11100110b);
 *      Res is equal to 2
 *      @endcode
 *
 * @param[in] Data Input data
 *
 * @retval Bit position
 *
 * @reqs    SWS_Bfx_91004, SWS_Bfx_00139
 */
uint8 Bfx_CountLeadingSigns_s64( sint64 Data )
{
    uint8 Count = 0u;

    for( uint8 i = 62u; i < 64u; i-- )
    {
        if( ( ( Data >> i ) & 0x01 ) != ( ( Data >> ( i + 1 ) ) & 0x01 ) )
        {
            break;
        }
        Count++;
    }

    return Count;
}

/**
 * @brief  **8 bit Count Leading Zeros**
 *
 * Count the number of consecutive zeros in Data starting with the most significant bit and return
 * the result
 *
 * **Example:**
 *      @code
 *      Res = Bfx_CountLeadingZeros_u64(00100110b);
 *      Res is equal to 2
 *      @endcode
 *
 * @param[in] Data Input data
 *
 * @retval Bit position
 *
 * @reqs    SWS_Bfx_91005, SWS_Bfx_00141
 */
uint8 Bfx_CountLeadingZeros_u64( uint64 Data )
{
    uint8 Count       = 0u;
    uint64 BitChecker = 0x8000000000000000u;

    while( ( Data & BitChecker ) == 0u )
    {
        Count++;
        BitChecker >>= 1u;
    }

    return Count;
}

#endif /* BFX_64BITS_H */
