/**
 * @file    Test_Bfx_32bit.c
 * @brief   **Unit Test for the 32 Bit Handling Routines**
 *
 * AUTOSAR Library routines are the part of system services in AUTOSAR architecture and below figure
 * shows position of AUTOSAR library in layered architecture.
 */
#include "unity.h"
#include "Std_Types.h"
#include "Bfx_32bits.h"

void setUp( void )
{
}

void tearDown( void )
{
}

/**
 * @brief   **Test set bit 18**
 *
 * The test validates if bit 18 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x00040000.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u32u8__bit18( void )
{
    uint32 Data = 0u;
    Bfx_SetBit_u32u8( &Data, 18u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x00040000, "Bit 18 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 31**
 *
 * The test validates if bit 31 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x80000000.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u32u8__bit31( void )
{
    uint32 Data = 0u;
    Bfx_SetBit_u32u8( &Data, 31u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x80000000, "Bit 31 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 18**
 *
 * The test validates if bit 18 is clear over a varible with value 0xFF, to pass data tested should have
 * a value of 0xFB.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u32u8__bit18( void )
{
    uint32 Data = 0xFFFFFFFFu;
    Bfx_ClrBit_u32u8( &Data, 18u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0xFFFBFFFF, "Bit 18 was not clear as supposed to be" );
}

/**
 * @brief   **Test clear bit 31**
 *
 * The test validates if bit 31 is clear over a varible with value 0xFF, to pass data tested should have
 * a value of 0x7FFFFFFF.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u32u8__bit31( void )
{
    uint32 Data = 0xFFFFFFFFu;
    Bfx_ClrBit_u32u8( &Data, 31u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x7FFFFFFF, "Bit 31 was not clear as supposed to be" );
}

/**
 * @brief   **Test get bit 19**
 *
 * The test validates if we get bit 19 over a varible with value 0x8A, to pass the return value
 * should be TRUE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u32u8_u8__true( void )
{
    uint32 Data = 0x008A0000u;
    boolean Bit = Bfx_GetBit_u32u8_u8( Data, 19u );
    TEST_ASSERT_MESSAGE( Bit == TRUE, "Bit is not TRUE as supposed to be" );
}

/**
 * @brief   **Test get bit 20**
 *
 * The test validates if we get bit 20 over a varible with value 0x8A, to pass the return value
 * should be FALSE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u32u8_u8__false( void )
{
    uint32 Data = 0x008A0000u;
    boolean Bit = Bfx_GetBit_u32u8_u8( Data, 20u );
    TEST_ASSERT_MESSAGE( Bit == FALSE, "Bit is not FALSE as supposed to be" );
}

/**
 * @brief   **Test setting multiple bits**
 *
 * The test validates if we can set 3 bits starting at bit 4 over a varible with value 0x8A, to pass
 * data tested should have a value of 0xFA.
 * 
 * @test    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void test__Bfx_SetBits_u32u8u8u8__mask1( void )
{
    uint32 Data = 0x8Au;
    Bfx_SetBits_u32u8u8u8( &Data, 4u, 3u, 1u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0xFAu, "Value is not 0xFA as supposed to be" );
}

/**
 * @brief   **Test clearing multiple bits**
 *
 * The test validates if we can clear 3 bits starting at bit 4 over a varible with value 0xFA, to pass
 * data tested should have a value of 0x8A.
 * 
 * @test    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void test__Bfx_SetBits_u32u8u8u8__mask0( void )
{
    uint32 Data = 0xFAu;
    Bfx_SetBits_u32u8u8u8( &Data, 4u, 3u, 0u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x8Au, "Value is not 0x8A as supposed to be" );
}

/**
 * @brief   **Test getting 3 bits**
 *
 * The test validates if we can get 3 bits starting at bit 4 over a varible with value 0x67, to pass
 * data tested should have a value of 0x06.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u32u8u8_u32__3bits( void )
{
    uint32 Data = 0x67u;
    Data        = Bfx_GetBits_u32u8u8_u32( Data, 4u, 3u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x06u, "Value is not 0x06 as supposed to be" );
}

/**
 * @brief   **Test getting 4 bits**
 *
 * The test validates if we can get 4 bits starting at bit 1 over a varible with value 0x7A, to pass
 * data tested should have a value of 0x03.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u32u8u8_u32__4bits( void )
{
    uint8 Data = 0x67u;
    Data       = Bfx_GetBits_u32u8u8_u32( Data, 1u, 4u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x03u, Data, "Value is not 0x03 as supposed to be" );
}

/**
 * @brief   **Test setting 4 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF0 over a varible with value
 * 0x67, to pass data tested should have a value of 0xF7.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u32u32__4bits( void )
{
    uint32 Data = 0x67u;
    Bfx_SetBitMask_u32u32( &Data, 0xF0u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0xF7u, "Value is not 0xF7 as supposed to be" );
}

/**
 * @brief   **Test setting 6 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF600 over a varible with value
 * 0x6700, to pass data tested should have a value of 0xF700.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u32u32__6bits( void )
{
    uint32 Data = 0x6700u;
    Bfx_SetBitMask_u32u32( &Data, 0xF600u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0xF700u, "Value is not 0xF700 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF0 over a varible with value
 * 0x67, to pass data tested should have a value of 0x07.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045 
 */
void test__Bfx_ClrBitMask_u32u32__4bits( void )
{
    uint32 Data = 0x67u;
    Bfx_ClrBitMask_u32u32( &Data, 0xF0u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x07u, "Value is not 0x07 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF6 over a varible with value
 * 0x67, to pass data tested should have a value of 0x01.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045  
 */
void test__Bfx_ClrBitMask_u32u32__6bits( void )
{
    uint32 Data = 0x6700u;
    Bfx_ClrBitMask_u32u32( &Data, 0xF600u );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( Data, 0x0100u, "Value is not 0x0100 as supposed to be" );
}

/**
 * @brief   **Test Mask of bits to true**
 *
 * The test validates if all the bit set of mask of with a value of 0x90 over a varible with value
 * 0xB3, to pass returned value should be TRUE.
 * 
 * @test  SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
void test__Bfx_TstBitMask_u32u32_u8__true( void )
{
    uint32 Data = 0xB3u;
    boolean Tst = Bfx_TstBitMask_u32u32_u8( Data, 0x90u );
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
void test__Bfx_TstBitMask_u32u32_u8__false( void )
{
    uint32 Data = 0xB3u;
    boolean Tst = Bfx_TstBitMask_u32u32_u8( Data, 0xF0u );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test at least one bit Mask to true**
 *
 * The test validates if at least one the bit set of mask with a value of 0xF0 over a varible with value
 * 0xB3, to pass returned value should be TRUE.
 * 
 * @test    SWS_Bfx_00051, SWS_Bfx_00055
 */
void test__Bfx_TstBitLnMask_u32u32_u8__true( void )
{
    uint32 Data = 0xB3u;
    boolean Tst = Bfx_TstBitLnMask_u32u32_u8( Data, 0xF0u );
    TEST_ASSERT_MESSAGE( Tst == TRUE, "Value is not TRUE as supposed to be" );
}

/**
 * @brief   **Test at least one bit Mask to false**
 *
 * The test validates if none of the the bits set of mask with a value of 0x48 over a varible with value
 * 0xB3, to pass returned value should be FALSE.
 * 
 * @test    SWS_Bfx_00051, SWS_Bfx_00055
 */
void test__Bfx_TstBitLnMask_u32u32_u8__false( void )
{
    uint32 Data = 0xB3u;
    boolean Tst = Bfx_TstBitLnMask_u32u32_u8( Data, 0x48u );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test Parity**
 *
 * The test validates if parity to one is TRUE over a variable with value 0xA5A5A5A5u, to pass the returned
 * variable should be TRUE
 * 
 * @test    SWS_Bfx_00056, SWS_Bfx_00060
 */
void test__Bfx_TstParityEven_u32_u8__true( void )
{
    uint32 Data = 0xA5A5A5A5u;
    boolean Tst = Bfx_TstParityEven_u32_u8( Data );
    TEST_ASSERT_MESSAGE( Tst == TRUE, "Value is not TRUE as supposed to be" );
}

/**
 * @brief   **Test Non-Parity**
 *
 * The test validates if parity to one is FALSE over a variable with value 0xA1, to pass the returned
 * variable should be FALSE
 * 
 * @test    SWS_Bfx_00056, SWS_Bfx_00060
 */
void test__Bfx_TstParityEven_u32_u8__false( void )
{
    uint32 Data = 0xA1A5A5A5u;
    boolean Tst = Bfx_TstParityEven_u32_u8( Data );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test toggle bits**
 *
 * The test validates if the bits can be toggle over a varible with value 0x1100FFAAu, to pass Data should
 * be equal to 0x55.
 * 
 * @test    SWS_Bfx_00061, SWS_Bfx_00065
 */
void test__Bfx_ToggleBits_u32( void )
{
    uint32 Data = 0x1100FFAAu;
    Bfx_ToggleBits_u32( &Data );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xEEFF0055, Data, "Value is not 0xEEFF0055 as supposed to be" );
}

/**
 * @brief   **Test toggle bits with a Mask**
 *
 * The test validates if the bits set on tha mask 0xF0 can toggle the bits over a varible with value 0xAAAAAAAAu,
 * to pass Data should be equal to 0x5AA5AA55.
 * 
 * @test    SWS_Bfx_00066, SWS_Bfx_00069
 */
void test__Bfx_ToggleBitMask_u32u32( void )
{
    uint32 Data = 0xAAAAAAAAu;
    Bfx_ToggleBitMask_u32u32( &Data, 0xF00F00FF );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x5AA5AA55, Data, "Value is not 0x5AA5AA55 as supposed to be" );
}

/**
 * @brief   **Test shift to the right 20 bits**
 *
 * The test validates a shift to the right by 20 bits over a varible with value 0x00AA0000u, to pass Data
 * should be equal to 0x0000000A.
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u32u8__20bits( void )
{
    uint32 Data = 0x00AA0000u;
    Bfx_ShiftBitRt_u32u8( &Data, 20 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0000000A, Data, "Value is not 0x0000000A as supposed to be" );
}

/**
 * @brief   **Test shift to the right 24 bits**
 *
 * The test validates a shift to the right by 24 bits over a varible with value 0x00AA0000u, to pass Data
 * should be equal to 0x00.
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u32u8__24bits( void )
{
    uint32 Data = 0x00AA0000u;
    Bfx_ShiftBitRt_u32u8( &Data, 24 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x00, Data, "Value is not 0x00 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 20 bits**
 *
 * The test validates a shift to the left by 20 bits over a varible with value 0xAA, to pass Data
 * should be equal to 0x0AA00000.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u32u8__20bits( void )
{
    uint32 Data = 0x000000AAu;
    Bfx_ShiftBitLt_u32u8( &Data, 20 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0AA00000, Data, "Value is not 0x0AA00000 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 16 bits**
 *
 * The test validates a shift to the left by 16 bits over a varible with value 0x0000AA00u, to pass Data
 * should be equal to 0xAA000000.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u32u8__16bits( void )
{
    uint32 Data = 0x0000AA00u;
    Bfx_ShiftBitLt_u32u8( &Data, 16 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xAA000000, Data, "Value is not 0xAA000000 as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 4 bits**
 *
 * The test validates a rotation to the right by 4 bits over a varible with value 0x5A, to pass Data
 * should be equal to 0xA5.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u32u8__4bits( void )
{
    uint32 Data = 0x0000005Au;
    Bfx_RotBitRt_u32u8( &Data, 4 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xA0000005, Data, "Value is not 0xA0000005 as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 7 bits**
 *
 * The test validates a rotation to the right by 7 bits over a varible with value 0x07, to pass Data
 * should be equal to 0x0E000000.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u32u8_7bits( void )
{
    uint32 Data = 0x00000007u;
    Bfx_RotBitRt_u32u8( &Data, 7 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0E000000, Data, "Value is not 0x0E000000 as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 26 bits**
 *
 * The test validates a rotation to the left by 16 bits over a varible with value 0x003A0000u, to pass Data
 * should be equal to 0x0000003A.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u32u8__16bits( void )
{
    uint32 Data = 0x003A0000u;
    Bfx_RotBitLt_u32u8( &Data, 16 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x0000003A, Data, "Value is not 0x000000A3 as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 7 bits**
 *
 * The test validates a rotation to the left by 7 bits over a varible with value 0x07000000, to pass Data
 * should be equal to 0x83000000.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u32u8__7bits( void )
{
    uint32 Data = 0x07000000u;
    Bfx_RotBitLt_u32u8( &Data, 7 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x80000003, Data, "Value is not 0x80000003 as supposed to be" );
}

/**
 * @brief   **Test copy bit 6**
 *
 * The test validates replacing bit 1 from a value of 0x22 on bit 6 over a varible with value 0xA1,
 * to pass Data should be equal to 0xE1.
 * 
 * @test    SWS_Bfx_00101, SWS_Bfx_00108
 */
void test__Bfx_CopyBit_u32u8u32u8__bit6( void )
{
    uint32 Data = 0xA1u;
    Bfx_CopyBit_u32u8u32u8( &Data, 6, 0x22, 1 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xE1, Data, "Value is not 0xE1 as supposed to be" );
}

/**
 * @brief   **Test put pattern of 4 bits**
 *
 * The test validates puttin a pattern of 4 bits starting from bit 1 over a varible with value 0xF0,
 * to pass Data should be equal to 0xE6.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u32u8u8u32__4bits( void )
{
    uint32 Data = 0xF0u;
    Bfx_PutBits_u32u8u8u32( &Data, 1, 4, 0x03 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xE6, Data, "Value is not 0xE6 as supposed to be" );
}

/**
 * @brief   **Test put pattern of 3 bits**
 *
 * The test validates puttin a pattern of 3 bits starting from bit 4 over a varible with value 0xEA,
 * to pass Data should be equal to 0xBA.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u32u8u8u32__3bits( void )
{
    uint32 Data = 0xEAu;
    Bfx_PutBits_u32u8u8u32( &Data, 4, 3, 0x03 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xBA, Data, "Value is not 0xBA as supposed to be" );
}

/**
 * @brief   **Test put pattern bit with Mask**
 *
 * The test validates puttin a pattern of bits using a mask of 0xDC over a varible with value 0xE0,
 * to pass Data should be equal to 0xED.
 * 
 * @test    SWS_Bfx_00120, SWS_Bfx_00124
 */
void test__Bfx_PutBitsMask_u32u32u32__3bits( void )
{
    uint32 Data = 0xE0u;
    Bfx_PutBitsMask_u32u32u32( &Data, 0xCD, 0x0F );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xED, Data, "Value is not 0xED as supposed to be" );
}

/**
 * @brief   **Test put bit 4 to TRUE**
 *
 * The test validates if the bit 4 is set over a varible with value 0xE7, to pass Data should be
 * equal to 0xF7.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u32u8u8__bit4true( void )
{
    uint32 Data = 0xE7u;
    Bfx_PutBit_u32u8u8( &Data, 4, TRUE );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xF7, Data, "Value is not 0xF7 as supposed to be" );
}

/**
 * @brief   **Test put bit 2 to FALSE**
 *
 * The test validates if the bit 2 is clear over a varible with value 0xE7, to pass Data should be
 * equal to 0xF3.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u32u8u8__bit2false( void )
{
    uint32 Data = 0xE7u;
    Bfx_PutBit_u32u8u8( &Data, 2, FALSE );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xE3, Data, "Value is not 0xE3 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 11 bits**
 *
 * The test validates a shift to the left by 11 bits over a varible with value 0x0076, to pass Data
 * should be equal to 0x00B0.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__3leftp( void )
{
    uint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0x76000000, 3 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x7FFFFFFF, Shifted, "Value is not 0x7FFFFFFF as supposed to be" );
}

/**
 * @brief   **Test shift to the left 3 bits no saturation**
 *
 * The test validates a shift to the left by 3 bits over a varible with value 0x06, to pass Data
 * should be equal to 0x7F.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__3leftp_nosaturation( void )
{
    uint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0x0600, 3 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x3000, Shifted, "Value is not 0x3000 as supposed to be" );
}

/**
 * @brief   **Test negative shift to the left 3 bits saturation**
 *
 * The test validates a shift to the left by 3 bits over a signed varible with value 0xE600, to pass Data
 * should be equal to 0x0E00.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__3leftn( void )
{
    uint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0xE6000000, 3 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x80000000, Shifted, "Value is not 0x80000000 as supposed to be" );
}

/**
 * @brief   **Test negative shift to the left 3 bits saturation**
 *
 * The test validates a shift to the left by 3 bits over a signed varible with value 0xF800, to pass Data
 * should be equal to 0xC000.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__3leftn_nosaturation( void )
{
    uint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0xF8000000, 3 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xC0000000, Shifted, "Value is not 0xC0000000 as supposed to be" );
}


/**
 * @brief   **Test shift to the right 11 bits**
 *
 * The test validates a shift to the right by 11 bits over a variable with value 0x7600, to pass Data
 * should be equal to 0x0E.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__11righp( void )
{
    sint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0x7006, -11 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0x000E, Shifted, "Value is not 0x000E as supposed to be" );
}

/**
 * @brief   **Test negative shift to the right 3 bits**
 *
 * The test validates a shift to the right by 3 bits over a signed variable with value 0xE6, to pass Data
 * should be equal to 0xFC.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s32s8_s32__3righn( void )
{
    sint32 Shifted;
    Shifted = Bfx_ShiftBitSat_s32s8_s32( 0xE6000000, -11 );
    TEST_ASSERT_EQUAL_HEX32_MESSAGE( 0xFFFCC000, Shifted, "Value is not 0xFFFCC000 as supposed to be" );
}

/**
 * @brief   **Test count 3 ones**
 *
 * The test validates if the three most significant bits are one over a varible with value 0xE6,
 * to pass Ones should be equal to 3.
 * 
 * @test    SWS_Bfx_91003, SWS_Bfx_00137
 */
void test__Bfx_CountLeadingOnes_u32__3ones( void )
{
    uint8 Ones;
    Ones = Bfx_CountLeadingOnes_u32( 0xFF600000 );
    TEST_ASSERT_EQUAL_MESSAGE( 8, Ones, "Value is not 3 as supposed to be" );
}

/**
 * @brief   **Test signed count 2 ones**
 *
 * The test validates if the two most significant bits are one over a signed varible with value 0xE6,
 * to pass Bits should be equal to 2.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s32__2ones( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s32( 0xE6 );
    TEST_ASSERT_EQUAL_MESSAGE( 2, Bits, "Value is not 2 as supposed to be" );
}

/**
 * @brief   **Test signed count 4 zeroes**
 *
 * The test validates if the four most significant bits are zero over a signed varible with value 0x06,
 * to pass Bits should be equal to 4.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s32__4zeroes( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s32( 0x06 );
    TEST_ASSERT_EQUAL_MESSAGE( 4, Bits, "Value is not 4 as supposed to be" );
}

/**
 * @brief   **Test count 19 zeroes**
 *
 * The test validates if the three most significant bits are zero over a varible with value 0x00001600,
 * to pass Zeroes should be equal to 19.
 * 
 * @test    SWS_Bfx_91005, SWS_Bfx_00141
 */
void test__Bfx_CountLeadingZeros_u32__19zeroes( void )
{
    uint8 Zeroes;
    Zeroes = Bfx_CountLeadingZeros_u32( 0x00001600 );
    TEST_ASSERT_EQUAL_MESSAGE( 19, Zeroes, "Value is not 19 as supposed to be" );
}
