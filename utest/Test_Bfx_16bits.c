/**
 * @file    Test_Bfx_16bits.c
 * @brief   **Unit Test for the 16 Bit Handling Routines**
 *
 * AUTOSAR Library routines are the part of system services in AUTOSAR architecture and below figure
 * shows position of AUTOSAR library in layered architecture.
 */
#include "unity.h"
#include "Std_Types.h"
#include "Bfx_16bits.h"

void setUp( void )
{
}

void tearDown( void )
{
}

/**
 * @brief   **Test set bit 10**
 *
 * The test validates if bit 10 is set over a varible with value 0x0000, to pass data tested should have
 * a value of 0x0004.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u16u8__bit10( void )
{
    uint16 Data = 0u;
    Bfx_SetBit_u16u8( &Data, 10u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x0400, "Bit 10 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 15**
 *
 * The test validates if bit 15 is set over a varible with value 0x0000, to pass data tested should have
 * a value of 0x8000.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u16u8__bit15( void )
{
    uint16 Data = 0u;
    Bfx_SetBit_u16u8( &Data, 15u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x8000, "Bit 15 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 10**
 *
 * The test validates if bit 10 is clear over a varible with value 0xFFFF, to pass data tested should have
 * a value of 0xFBFF.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u16u8__bit10( void )
{
    uint16 Data = 0xFFFFu;
    Bfx_ClrBit_u16u8( &Data, 10u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0xFBFF, "Bit 10 was not clear as supposed to be" );
}

/**
 * @brief   **Test clear bit 15**
 *
 * The test validates if bit 15 is clear over a varible with value 0xFFFF, to pass data tested should have
 * a value of 0x7FFF.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u16u8__bit15( void )
{
    uint16 Data = 0xFFFFu;
    Bfx_ClrBit_u16u8( &Data, 15u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x7FFF, "Bit 15 was not clear as supposed to be" );
}

/**
 * @brief   **Test get bit 11**
 *
 * The test validates if we get bit 11 over a varible with value 0x8A00, to pass the return value
 * should be TRUE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u16u8_u8__true( void )
{
    uint16 Data  = 0x8A00u;
    boolean Bit = Bfx_GetBit_u16u8_u8( Data, 11u );
    TEST_ASSERT_MESSAGE( Bit == TRUE, "Bit is not TRUE as supposed to be" );
}

/**
 * @brief   **Test get bit 12**
 *
 * The test validates if we get bit 12 over a varible with value 0x8A, to pass the return value
 * should be FALSE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u16u8_u8__false( void )
{
    uint16 Data  = 0x8A00u;
    boolean Bit = Bfx_GetBit_u16u8_u8( Data, 12u );
    TEST_ASSERT_MESSAGE( Bit == FALSE, "Bit is not FALSE as supposed to be" );
}

/**
 * @brief   **Test setting multiple bits**
 *
 * The test validates if we can set 6 bits starting at bit 4 over a varible with value 0x008A, to pass
 * data tested should have a value of 0x03FA.
 * 
 * @test    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void test__Bfx_SetBits_u16u8u8u8__mask1( void )
{
    uint16 Data = 0x8Au;
    Bfx_SetBits_u16u8u8u8( &Data, 4u, 6u, 1u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x3FAu, "Value is not 0xFA as supposed to be" );
}

/**
 * @brief   **Test clearing multiple bits**
 *
 * The test validates if we can clear 6 bits starting at bit 4 over a varible with value 0x03FA, to pass
 * data tested should have a value of 0x8A.
 * 
 * @test    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void test__Bfx_SetBits_u16u8u8u8__mask0( void )
{
    uint16 Data = 0x03FAu;
    Bfx_SetBits_u16u8u8u8( &Data, 4u, 6u, 0u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x000Au, "Value is not 0x008A as supposed to be" );
}

/**
 * @brief   **Test getting 6 bits**
 *
 * The test validates if we can get 6 bits starting at bit 4 over a varible with value 0x0367, to pass
 * data tested should have a value of 0x06.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u16u8u8_u16__3bits( void )
{
    uint16 Data = 0x0367u;
    Data       = Bfx_GetBits_u16u8u8_u16( Data, 4u, 6u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x0036u, "Value is not 0x0036 as supposed to be" );
}

/**
 * @brief   **Test getting 4 bits**
 *
 * The test validates if we can get 8 bits starting at bit 1 over a varible with value 0x067A, to pass
 * data tested should have a value of 0x003D.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u16u8u8_u16__4bits( void )
{
    uint16 Data = 0x067Au;
    Data       = Bfx_GetBits_u16u8u8_u16( Data, 1u, 8u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x003Du, "Value is not 0x003C as supposed to be" );
}

/**
 * @brief   **Test setting 4 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF0F0 over a varible with value
 * 0x6700, to pass data tested should have a value of 0xF7F0.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u16u16__4bits( void )
{
    uint16 Data = 0x6700u;
    Bfx_SetBitMask_u16u16( &Data, 0xF0F0u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0xF7F0u, "Value is not 0xF7F0 as supposed to be" );
}

/**
 * @brief   **Test setting 6 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF600 over a varible with value
 * 0x6700, to pass data tested should have a value of 0xF700.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u16u16__6bits( void )
{
    uint16 Data = 0x6700u;
    Bfx_SetBitMask_u16u16( &Data, 0xF600u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0xF700u, "Value is not 0xF700 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF0 over a varible with value
 * 0x67, to pass data tested should have a value of 0x07.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045  
 */
void test__Bfx_ClrBitMask_u16u16__4bits( void )
{
    uint16 Data = 0x6700u;
    Bfx_ClrBitMask_u16u16( &Data, 0xF000u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x0700u, "Value is not 0x0700 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF6 over a varible with value
 * 0x67, to pass data tested should have a value of 0x01.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045  
 */
void test__Bfx_ClrBitMask_u16u16__6bits( void )
{
    uint16 Data = 0x6700u;
    Bfx_ClrBitMask_u16u16( &Data, 0xF600u );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( Data, 0x0100u, "Value is not 0x0100 as supposed to be" );
}

/**
 * @brief   **Test Mask of bits to true**
 *
 * The test validates if all the bit set of mask of with a value of 0x9000 over a varible with value
 * 0xB300, to pass returned value should be TRUE.
 * 
 * @test  SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
void test__Bfx_TstBitMask_u16u16_u8__true( void )
{
    uint16 Data  = 0xB300u;
    boolean Tst = Bfx_TstBitMask_u16u16_u8( Data, 0x9000u );
    TEST_ASSERT_MESSAGE( Tst == TRUE, "Value is not TRUE as supposed to be" );
}

/**
 * @brief   **Test Mask of bits to false**
 *
 * The test validates if all the bit set of mask of with a value of 0xF0 over a varible with value
 * 0xB3, to pass returned value should be FALSE.
 * 
 * @test  SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
void test__Bfx_TstBitMask_u16u16_u8__false( void )
{
    uint16 Data  = 0xB300u;
    boolean Tst = Bfx_TstBitMask_u16u16_u8( Data, 0xF000u );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test at least one bit Mask to true**
 *
 * The test validates if at least one the bit set of mask with a value of 0xF000 over a varible with value
 * 0xB300, to pass returned value should be TRUE.
 * 
 * @test    SWS_Bfx_00051, SWS_Bfx_00055
 */
void test__Bfx_TstBitLnMask_u16u16_u8__true( void )
{
    uint16 Data  = 0xB300u;
    boolean Tst = Bfx_TstBitLnMask_u16u16_u8( Data, 0xF000u );
    TEST_ASSERT_MESSAGE( Tst == TRUE, "Value is not TRUE as supposed to be" );
}

/**
 * @brief   **Test at least one bit Mask to false**
 *
 * The test validates if none of the the bits set of mask with a value of 0x4800 over a varible with value
 * 0xB300, to pass returned value should be FALSE.
 * 
 * @test    SWS_Bfx_00051, SWS_Bfx_00055
 */
void test__Bfx_TstBitLnMask_u16u16_u8__false( void )
{
    uint16 Data  = 0xB300u;
    boolean Tst = Bfx_TstBitLnMask_u16u16_u8( Data, 0x4800u );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test Parity**
 *
 * The test validates if parity to one is TRUE over a variable with value 0xA0A0, to pass the returned
 * variable should be TRUE
 * 
 * @test    SWS_Bfx_00056, SWS_Bfx_00060
 */
void test__Bfx_TstParityEven_u16_u8__true( void )
{
    uint16 Data  = 0xA0A0u;
    boolean Tst = Bfx_TstParityEven_u16_u8( Data );
    TEST_ASSERT_MESSAGE( Tst == TRUE, "Value is not TRUE as supposed to be" );
}

/**
 * @brief   **Test Non-Parity**
 *
 * The test validates if parity to one is FALSE over a variable with value 0xA010, to pass the returned
 * variable should be FALSE
 * 
 * @test    SWS_Bfx_00056, SWS_Bfx_00060
 */
void test__Bfx_TstParityEven_u16_u8__false( void )
{
    uint16 Data  = 0xA010u;
    boolean Tst = Bfx_TstParityEven_u16_u8( Data );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test toggle bits**
 *
 * The test validates if the bits can be toggle over a varible with value 0xA0A0, to pass Data should
 * be equal to 0x5050.
 * 
 * @test    SWS_Bfx_00061, SWS_Bfx_00065
 */
void test__Bfx_ToggleBits_u16( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ToggleBits_u16( &Data );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x5F5F, Data, "Value is not 0x5050 as supposed to be" );
}

/**
 * @brief   **Test toggle bits with a Mask**
 *
 * The test validates if the bits set on tha mask 0xF0F0 can toggle the bits over a varible with value 0xA0A0,
 * to pass Data should be equal to 0x5050.
 * 
 * @test    SWS_Bfx_00066, SWS_Bfx_00069
 */
void test__Bfx_ToggleBitMask_u16u16( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ToggleBitMask_u16u16( &Data, 0xF0F0 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x5050, Data, "Value is not 0x5050 as supposed to be" );
}

/**
 * @brief   **Test shift to the right 8 bits**
 *
 * The test validates a shift to the right by 8 bits over a varible with value 0xA0A0, to pass Data
 * should be equal to 0x00A0.
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u16u8__8bits( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ShiftBitRt_u16u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x00A0, Data, "Value is not 0x00A0 as supposed to be" );
}

/**
 * @brief   **Test shift to the right 12 bits**
 *
 * The test validates a shift to the right by 12 bits over a varible with value 0xA0A0, to pass Data
 * should be equal to 0x000A
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u16u8__12bits( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ShiftBitRt_u16u8( &Data, 12 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x000A, Data, "Value is not 0x000A as supposed to be" );
}

/**
 * @brief   **Test shift to the left 8 bits**
 *
 * The test validates a shift to the left by 8 bits over a varible with value 0xA0A0, to pass Data
 * should be equal to 0xA000.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u16u8__8bits( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ShiftBitLt_u16u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xA000, Data, "Value is not 0xA000 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 12 bits**
 *
 * The test validates a shift to the left by 12 bits over a varible with value 0xA0A0, to pass Data
 * should be equal to 0x0000.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u16u8__12bits( void )
{
    uint16 Data = 0xA0A0u;
    Bfx_ShiftBitLt_u16u8( &Data, 12 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x0000, Data, "Value is not 0x0000 as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 8 bits**
 *
 * The test validates a rotation to the right by 8 bits over a varible with value 0x5A00, to pass Data
 * should be equal to 0x005A.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u16u8__4bits( void )
{
    uint16 Data = 0x5A00u;
    Bfx_RotBitRt_u16u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x005A, Data, "Value is not 0x005A as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 11 bits**
 *
 * The test validates a rotation to the right by 11 bits over a varible with value 0x0700, to pass Data
 * should be equal to 0xE000.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u16u8__11bits( void )
{
    uint16 Data = 0x0700u;
    Bfx_RotBitRt_u16u8( &Data, 11 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xE000, Data, "Value is not 0xE000 as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 8 bits**
 *
 * The test validates a rotation to the left by 8 bits over a varible with value 0x3A00, to pass Data
 * should be equal to 0x003A.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u16u8__8bits( void )
{
    uint16 Data = 0x3A00u;
    Bfx_RotBitLt_u16u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x003A, Data, "Value is not 0x003A as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 11 bits**
 *
 * The test validates a rotation to the left by 11 bits over a varible with value 0x0700, to pass Data
 * should be equal to 0x0038.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u16u8__11bits( void )
{
    uint16 Data = 0x0700u;
    Bfx_RotBitLt_u16u8( &Data, 11 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x0038, Data, "Value is not 0x0038 as supposed to be" );
}

/**
 * @brief   **Test copy bit 10**
 *
 * The test validates replacing bit 1 from a value of 0x0222 on bit 10 over a varible with value 0x04A1,
 * to pass Data should be equal to 0x00A1.
 * 
 * @test    SWS_Bfx_00101, SWS_Bfx_00108
 */
void test__Bfx_CopyBit_u16u8u16u8__bit10( void )
{
    uint16 Data = 0x00A1u;
    Bfx_CopyBit_u16u8u16u8( &Data, 10, 0x0222, 1 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x04A1, Data, "Value is not 0x04A1 as supposed to be" );
}

/**
 * @brief   **Test put pattern of 4 bits**
 *
 * The test validates puttin a pattern of 4 bits starting from bit 1 over a varible with value 0xF0,
 * to pass Data should be equal to 0xE6.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u16u8u8u16__4bits( void )
{
    uint16 Data = 0x00F0u;
    Bfx_PutBits_u16u8u8u16( &Data, 2, 12, 0x0303 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x0C0C, Data, "Value is not 0x0C0C as supposed to be" );
}

/**
 * @brief   **Test put pattern of 3 bits**
 *
 * The test validates puttin a pattern of 3 bits starting from bit 4 over a varible with value 0xEA,
 * to pass Data should be equal to 0xBA.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u16u8u8u16__3bits( void )
{
    uint16 Data = 0xE0A0u;
    Bfx_PutBits_u16u8u8u16( &Data, 4, 8, 0x53 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xE530, Data, "Value is not 0xE530 as supposed to be" );
}

/**
 * @brief   **Test put pattern bit with Mask**
 *
 * The test validates puttin a pattern of bits using a mask of 0xDC over a varible with value 0xE0,
 * to pass Data should be equal to 0xED.
 * 
 * @test    SWS_Bfx_00120, SWS_Bfx_00124
 */
void test__Bfx_PutBitsMask_u8u8u8__3bits( void )
{
    uint16 Data = 0xE000u;
    Bfx_PutBitsMask_u16u16u16( &Data, 0xCD00, 0x0F00 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xED00, Data, "Value is not 0xED as supposed to be" );
}

/**
 * @brief   **Test put bit 11 to TRUE**
 *
 * The test validates if the bit 11 is set over a varible with value 0xE700, to pass Data should be
 * equal to 0xEF00.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u16u8u8__bit11true( void )
{
    uint16 Data = 0xE700u;
    Bfx_PutBit_u16u8u8( &Data, 11, TRUE );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xEF00, Data, "Value is not 0xEF00 as supposed to be" );
}

/**
 * @brief   **Test put bit 13 to FALSE**
 *
 * The test validates if the bit 13 is clear over a varible with value 0xE700, to pass Data should be
 * equal to 0xC700.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u16u8u8__bit13false( void )
{
    uint16 Data = 0xE700u;
    Bfx_PutBit_u16u8u8( &Data, 13, FALSE );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xC700, Data, "Value is not 0xC700 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 11 bits**
 *
 * The test validates a shift to the left by 11 bits over a varible with value 0x0076, to pass Data
 * should be equal to 0x00B0.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__3leftp( void )
{
    uint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0x7600, 3 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x7FFF, Shifted, "Value is not 0x0130 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 3 bits no saturation**
 *
 * The test validates a shift to the left by 3 bits over a varible with value 0x06, to pass Data
 * should be equal to 0x7F.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__3leftp_nosaturation( void )
{
    uint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0x0600, 3 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x3000, Shifted, "Value is not 0x3000 as supposed to be" );
}

/**
 * @brief   **Test negative shift to the left 3 bits saturation**
 *
 * The test validates a shift to the left by 3 bits over a signed varible with value 0xE600, to pass Data
 * should be equal to 0x0E00.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__3leftn( void )
{
    uint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0xE600, 3 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x8000, Shifted, "Value is not 0x8000 as supposed to be" );
}

/**
 * @brief   **Test negative shift to the left 3 bits saturation**
 *
 * The test validates a shift to the left by 3 bits over a signed varible with value 0xF800, to pass Data
 * should be equal to 0xC000.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__3leftn_nosaturation( void )
{
    uint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0xF800, 3 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xC000, Shifted, "Value is not 0xC000 as supposed to be" );
}


/**
 * @brief   **Test shift to the right 11 bits**
 *
 * The test validates a shift to the right by 11 bits over a variable with value 0x7600, to pass Data
 * should be equal to 0x0E.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__11righp( void )
{
    sint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0x7006, -11 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0x000E, Shifted, "Value is not 0x000E as supposed to be" );
}

/**
 * @brief   **Test negative shift to the right 3 bits**
 *
 * The test validates a shift to the right by 3 bits over a signed variable with value 0xE6, to pass Data
 * should be equal to 0xFC.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s16s8_s16__3righn( void )
{
    sint16 Shifted;
    Shifted = Bfx_ShiftBitSat_s16s8_s16( 0xE600, -11 );
    TEST_ASSERT_EQUAL_HEX16_MESSAGE( 0xFFFC, Shifted, "Value is not 0xFFFC as supposed to be" );
}

/**
 * @brief   **Test count 11 ones**
 *
 * The test validates if the three most significant bits are one over a varible with value 0xFFE6,
 * to pass Ones should be equal to 11.
 * 
 * @test    SWS_Bfx_91003, SWS_Bfx_00137
 */
void test__Bfx_CountLeadingOnes_u16__3ones( void )
{
    uint8 Ones;
    Ones = Bfx_CountLeadingOnes_u16( 0xFFE6 );
    TEST_ASSERT_EQUAL_MESSAGE( 11, Ones, "Value is not 3 as supposed to be" );
}

/**
 * @brief   **Test signed count 10 ones**
 *
 * The test validates if the two most significant bits are one over a signed varible with value 0xFFE6,
 * to pass Bits should be equal to 10.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s16__10ones( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s16( 0xFFE6 );
    TEST_ASSERT_EQUAL_MESSAGE( 10, Bits, "Value is not 2 as supposed to be" );
}

/**
 * @brief   **Test signed count 12 zeroes**
 *
 * The test validates if the four most significant bits are zero over a signed varible with value 0x0006,
 * to pass Bits should be equal to 12.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s16__12zeroes( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s16( 0x0006 );
    TEST_ASSERT_EQUAL_MESSAGE( 12, Bits, "Value is not 4 as supposed to be" );
}

/**
 * @brief   **Test count 11 zeroes**
 *
 * The test validates if the three most significant bits are zero over a varible with value 0x0016,
 * to pass Zeroes should be equal to 11.
 * 
 * @test    SWS_Bfx_91005, SWS_Bfx_00141
 */
void test__Bfx_CountLeadingZeros_u16__11zeroes( void )
{
    uint8 Zeroes;
    Zeroes = Bfx_CountLeadingZeros_u16( 0x0016 );
    TEST_ASSERT_EQUAL_MESSAGE( 11, Zeroes, "Value is not 3 as supposed to be" );
}
