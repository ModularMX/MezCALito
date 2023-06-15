/**
 * @file    Test_Bfx_8bits.c
 * @brief   **Unit Test for the 8 Bit Handling Routines**
 *
 * AUTOSAR Library routines are the part of system services in AUTOSAR architecture and below figure
 * shows position of AUTOSAR library in layered architecture.
 */
#include "unity.h"
#include "Std_Types.h"
#include "Bfx_8bits.h"

void setUp( void )
{
}

void tearDown( void )
{
}

/**
 * @brief   **Test set bit 2**
 *
 * The test validates if bit 2 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x04.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u8u8__bit2( void )
{
    uint8 Data = 0u;
    Bfx_SetBit_u8u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x04, "Bit 2 was not set as supposed to be" );
}

/**
 * @brief   **Test set bit 7**
 *
 * The test validates if bit 7 is set over a varible with value 0x00, to pass data tested should have
 * a value of 0x80.
 * 
 * @test    SWS_Bfx_00001, SWS_Bfx_00002, SWS_Bfx_00008
 */
void test__Bfx_SetBit_u8u8__bit7( void )
{
    uint8 Data = 0u;
    Bfx_SetBit_u8u8( &Data, 7u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x80, "Bit 7 was not set as supposed to be" );
}

/**
 * @brief   **Test clear bit 2**
 *
 * The test validates if bit 2 is clear over a varible with value 0xFF, to pass data tested should have
 * a value of 0xFB.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u8u8__bit2( void )
{
    uint8 Data = 0xFFu;
    Bfx_ClrBit_u8u8( &Data, 2u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFB, "Bit 2 was not clear as supposed to be" );
}

/**
 * @brief   **Test clear bit 7**
 *
 * The test validates if bit 7 is clear over a varible with value 0xFF, to pass data tested should have
 * a value of 0xEF.
 * 
 * @test    SWS_Bfx_00010, SWS_Bfx_00011, SWS_Bfx_00015
 */
void test__Bfx_ClrBit_u8u8__bit7( void )
{
    uint8 Data = 0xFFu;
    Bfx_ClrBit_u8u8( &Data, 7u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x7F, "Bit 2 was not clear as supposed to be" );
}

/**
 * @brief   **Test get bit 3**
 *
 * The test validates if we get bit 3 over a varible with value 0x8A, to pass the return value
 * should be TRUE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u8u8_u8__true( void )
{
    uint8 Data  = 0x8Au;
    boolean Bit = Bfx_GetBit_u8u8_u8( Data, 3u );
    TEST_ASSERT_MESSAGE( Bit == TRUE, "Bit is not TRUE as supposed to be" );
}

/**
 * @brief   **Test get bit 4**
 *
 * The test validates if we get bit 4 over a varible with value 0x8A, to pass the return value
 * should be FALSE.
 * 
 * @test    SWS_Bfx_00016, SWS_Bfx_00017, SWS_Bfx_00020
 */
void test__Bfx_GetBit_u8u8_u8__false( void )
{
    uint8 Data  = 0x8Au;
    boolean Bit = Bfx_GetBit_u8u8_u8( Data, 4u );
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
void test__Bfx_SetBits_u8u8u8u8__mask1( void )
{
    uint8 Data = 0x8Au;
    Bfx_SetBits_u8u8u8u8( &Data, 4u, 3u, 1u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xFAu, "Value is not 0xFA as supposed to be" );
}

/**
 * @brief   **Test clearing multiple bits**
 *
 * The test validates if we can clear 3 bits starting at bit 4 over a varible with value 0xFA, to pass
 * data tested should have a value of 0x8A.
 * 
 * @test    SWS_Bfx_00021, SWS_Bfx_00022, SWS_Bfx_00025
 */
void test__Bfx_SetBits_u8u8u8u8__mask0( void )
{
    uint8 Data = 0xFAu;
    Bfx_SetBits_u8u8u8u8( &Data, 4u, 3u, 0u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x8Au, "Value is not 0x8A as supposed to be" );
}

/**
 * @brief   **Test getting 3 bits**
 *
 * The test validates if we can get 3 bits starting at bit 4 over a varible with value 0x67, to pass
 * data tested should have a value of 0x06.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u8u8u8_u8__3bits( void )
{
    uint8 Data = 0x67u;
    Data       = Bfx_GetBits_u8u8u8_u8( Data, 4u, 3u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x06u, "Value is not 0x06 as supposed to be" );
}

/**
 * @brief   **Test getting 4 bits**
 *
 * The test validates if we can get 4 bits starting at bit 1 over a varible with value 0x7A, to pass
 * data tested should have a value of 0x03.
 * 
 * @test    SWS_Bfx_00028, SWS_Bfx_00029, SWS_Bfx_00034
 */
void test__Bfx_GetBits_u8u8u8_u8__4bits( void )
{
    uint8 Data = 0x67u;
    Data       = Bfx_GetBits_u8u8u8_u8( Data, 1u, 4u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x03u, Data, "Value is not 0x03 as supposed to be" );
}

/**
 * @brief   **Test setting 4 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF0 over a varible with value
 * 0x67, to pass data tested should have a value of 0xF7.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u8u8__4bits( void )
{
    uint8 Data = 0x67u;
    Bfx_SetBitMask_u8u8( &Data, 0xF0u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF7u, "Value is not 0xF7 as supposed to be" );
}

/**
 * @brief   **Test setting 6 bits**
 *
 * The test validates if we can set a mask of bits with a value of 0xF6 over a varible with value
 * 0x67, to pass data tested should have a value of 0xF7.
 * 
 * @test    SWS_Bfx_00035, SWS_Bfx_00036, SWS_Bfx_00038
 */
void test__Bfx_SetBitMask_u8u8__6bits( void )
{
    uint8 Data = 0x67u;
    Bfx_SetBitMask_u8u8( &Data, 0xF6u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0xF7u, "Value is not 0xF7 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF0 over a varible with value
 * 0x67, to pass data tested should have a value of 0x07.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045  
 */
void test__Bfx_ClrBitMask_u8u8__4bits( void )
{
    uint8 Data = 0x67u;
    Bfx_ClrBitMask_u8u8( &Data, 0xF0u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x07u, "Value is not 0x07 as supposed to be" );
}

/**
 * @brief   **Test clearing 4 bits**
 *
 * The test validates if we can clear a mask of bits with a value of 0xF6 over a varible with value
 * 0x67, to pass data tested should have a value of 0x01.
 * 
 * @test  SWS_Bfx_00039, SWS_Bfx_00040, SWS_Bfx_00045  
 */
void test__Bfx_ClrBitMask_u8u8__6bits( void )
{
    uint8 Data = 0x67u;
    Bfx_ClrBitMask_u8u8( &Data, 0xF6u );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( Data, 0x01u, "Value is not 0x01 as supposed to be" );
}

/**
 * @brief   **Test Mask of bits to true**
 *
 * The test validates if all the bit set of mask of with a value of 0x90 over a varible with value
 * 0xB3, to pass returned value should be TRUE.
 * 
 * @test  SWS_Bfx_00046, SWS_Bfx_00047, SWS_Bfx_00050
 */
void test__Bfx_TstBitMask_u8u8_u8__true( void )
{
    uint8 Data  = 0xB3u;
    boolean Tst = Bfx_TstBitMask_u8u8_u8( Data, 0x90u );
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
void test__Bfx_TstBitMask_u8u8_u8__false( void )
{
    uint8 Data  = 0xB3u;
    boolean Tst = Bfx_TstBitMask_u8u8_u8( Data, 0xF0u );
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
void test__Bfx_TstBitLnMask_u8u8_u8__true( void )
{
    uint8 Data  = 0xB3u;
    boolean Tst = Bfx_TstBitLnMask_u8u8_u8( Data, 0xF0u );
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
void test__Bfx_TstBitLnMask_u8u8_u8__false( void )
{
    uint8 Data  = 0xB3u;
    boolean Tst = Bfx_TstBitLnMask_u8u8_u8( Data, 0x48u );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test Parity**
 *
 * The test validates if parity to one is TRUE over a variable with value 0xAA, to pass the returned
 * variable should be TRUE
 * 
 * @test    SWS_Bfx_00056, SWS_Bfx_00060
 */
void test__Bfx_TstParityEven_u8_u8__true( void )
{
    uint8 Data  = 0xAAu;
    boolean Tst = Bfx_TstParityEven_u8_u8( Data );
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
void test__Bfx_TstParityEven_u8_u8__false( void )
{
    uint8 Data  = 0xA1u;
    boolean Tst = Bfx_TstParityEven_u8_u8( Data );
    TEST_ASSERT_MESSAGE( Tst == FALSE, "Value is not FALSE as supposed to be" );
}

/**
 * @brief   **Test toggle bits**
 *
 * The test validates if the bits can be toggle over a varible with value 0xAA, to pass Data should
 * be equal to 0x55.
 * 
 * @test    SWS_Bfx_00061, SWS_Bfx_00065
 */
void test__Bfx_ToggleBits_u8( void )
{
    uint8 Data = 0xAAu;
    Bfx_ToggleBits_u8( &Data );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x55, Data, "Value is not 0x55 as supposed to be" );
}

/**
 * @brief   **Test toggle bits with a Mask**
 *
 * The test validates if the bits set on tha mask 0xF0 can toggle the bits over a varible with value 0xAA,
 * to pass Data should be equal to 0x50.
 * 
 * @test    SWS_Bfx_00066, SWS_Bfx_00069
 */
void test__Bfx_ToggleBitMask_u8u8( void )
{
    uint8 Data = 0xAAu;
    Bfx_ToggleBitMask_u8u8( &Data, 0xF0 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x5A, Data, "Value is not 0x5A as supposed to be" );
}

/**
 * @brief   **Test shift to the right 4 bits**
 *
 * The test validates a shift to the right by 4 bits over a varible with value 0xAA, to pass Data
 * should be equal to 0x0A.
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u8u8__4bits( void )
{
    uint8 Data = 0xAAu;
    Bfx_ShiftBitRt_u8u8( &Data, 4 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x0A, Data, "Value is not 0x0A as supposed to be" );
}

/**
 * @brief   **Test shift to the right 8 bits**
 *
 * The test validates a shift to the right by 8 bits over a varible with value 0xAA, to pass Data
 * should be equal to 0x00.
 * 
 * @test    SWS_Bfx_00070, SWS_Bfx_00075
 */
void test__Bfx_ShiftBitRt_u8u8__8bits( void )
{
    uint8 Data = 0xAAu;
    Bfx_ShiftBitRt_u8u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x00, Data, "Value is not 0x00 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 4 bits**
 *
 * The test validates a shift to the left by 4 bits over a varible with value 0xAA, to pass Data
 * should be equal to 0xA0.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u8u8__4bits( void )
{
    uint8 Data = 0xAAu;
    Bfx_ShiftBitLt_u8u8( &Data, 4 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xA0, Data, "Value is not 0xA0 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 8 bits**
 *
 * The test validates a shift to the left by 8 bits over a varible with value 0xAA, to pass Data
 * should be equal to 0x00.
 * 
 * @test    SWS_Bfx_00076, SWS_Bfx_00080
 */
void test__Bfx_ShiftBitLt_u8u8__8bits( void )
{
    uint8 Data = 0xAAu;
    Bfx_ShiftBitLt_u8u8( &Data, 8 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x00, Data, "Value is not 0x00 as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 4 bits**
 *
 * The test validates a rotation to the right by 4 bits over a varible with value 0x5A, to pass Data
 * should be equal to 0xA5.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u8u8__4bits( void )
{
    uint8 Data = 0x5Au;
    Bfx_RotBitRt_u8u8( &Data, 4 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xA5, Data, "Value is not 0xA5 as supposed to be" );
}

/**
 * @brief   **Test rotate to the right 7 bits**
 *
 * The test validates a rotation to the right by 7 bits over a varible with value 0x07, to pass Data
 * should be equal to 0x83.
 * 
 * @test    SWS_Bfx_00086, SWS_Bfx_00090
 */
void test__Bfx_RotBitRt_u8u8_7bits( void )
{
    uint8 Data = 0x07u;
    Bfx_RotBitRt_u8u8( &Data, 7 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x0E, Data, "Value is not 0x0E as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 4 bits**
 *
 * The test validates a rotation to the left by 4 bits over a varible with value 0x5A, to pass Data
 * should be equal to 0xA5.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u8u8__4bits( void )
{
    uint8 Data = 0x3Au;
    Bfx_RotBitLt_u8u8( &Data, 4 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xA3, Data, "Value is not 0xA3 as supposed to be" );
}

/**
 * @brief   **Test rotate to the left 7 bits**
 *
 * The test validates a rotation to the left by 7 bits over a varible with value 0x07, to pass Data
 * should be equal to 0x83.
 * 
 * @test    SWS_Bfx_00095, SWS_Bfx_00098
 */
void test__Bfx_RotBitLt_u8u8__7bits( void )
{
    uint8 Data = 0x07u;
    Bfx_RotBitLt_u8u8( &Data, 7 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x83, Data, "Value is not 0x83 as supposed to be" );
}

/**
 * @brief   **Test copy bit 6**
 *
 * The test validates replacing bit 1 from a value of 0x22 on bit 6 over a varible with value 0xA1,
 * to pass Data should be equal to 0xE1.
 * 
 * @test    SWS_Bfx_00101, SWS_Bfx_00108
 */
void test__Bfx_CopyBit_u8u8u8u8__bit6( void )
{
    uint8 Data = 0xA1u;
    Bfx_CopyBit_u8u8u8u8( &Data, 6, 0x22, 1 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xE1, Data, "Value is not 0xE1 as supposed to be" );
}

/**
 * @brief   **Test put pattern of 4 bits**
 *
 * The test validates puttin a pattern of 4 bits starting from bit 1 over a varible with value 0xF0,
 * to pass Data should be equal to 0xE6.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u8u8u8u8__4bits( void )
{
    uint8 Data = 0xF0u;
    Bfx_PutBits_u8u8u8u8( &Data, 1, 4, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xE6, Data, "Value is not 0xE6 as supposed to be" );
}

/**
 * @brief   **Test put pattern of 3 bits**
 *
 * The test validates puttin a pattern of 3 bits starting from bit 4 over a varible with value 0xEA,
 * to pass Data should be equal to 0xBA.
 * 
 * @test    SWS_Bfx_00110, SWS_Bfx_00112
 */
void test__Bfx_PutBits_u8u8u8u8__3bits( void )
{
    uint8 Data = 0xEAu;
    Bfx_PutBits_u8u8u8u8( &Data, 4, 3, 0x03 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xBA, Data, "Value is not 0xBA as supposed to be" );
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
    uint8 Data = 0xE0u;
    Bfx_PutBitsMask_u8u8u8( &Data, 0xCD, 0x0F );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xED, Data, "Value is not 0xED as supposed to be" );
}

/**
 * @brief   **Test put bit 4 to TRUE**
 *
 * The test validates if the bit 4 is set over a varible with value 0xE7, to pass Data should be
 * equal to 0xF7.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u8u8u8__bit4true( void )
{
    uint8 Data = 0xE7u;
    Bfx_PutBit_u8u8u8( &Data, 4, TRUE );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xF7, Data, "Value is not 0xF7 as supposed to be" );
}

/**
 * @brief   **Test put bit 2 to FALSE**
 *
 * The test validates if the bit 2 is clear over a varible with value 0xE7, to pass Data should be
 * equal to 0xF3.
 * 
 * @test    SWS_Bfx_00130, SWS_Bfx_00132
 */
void test__Bfx_PutBit_u8u8u8__bit2false( void )
{
    uint8 Data = 0xE7u;
    Bfx_PutBit_u8u8u8( &Data, 2, FALSE );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xE3, Data, "Value is not 0xE3 as supposed to be" );
}

/**
 * @brief   **Test shift to the left 3 bits**
 *
 * The test validates a shift to the left by 3 bits over a varible with value 0x76, to pass Data
 * should be equal to 0xB0.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s8s8_s8__3leftp( void )
{
    uint8 Shifted;
    Shifted = Bfx_ShiftBitSat_s8s8_s8( 3, 0x76 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xB0, Shifted, "Value is not 0xB0 as supposed to be" );
}

/**
 * @brief   **Test negative shift to the left 3 bits**
 *
 * The test validates a shift to the left by 3 bits over a signed varible with value 0xE6, to pass Data
 * should be equal to 0x30.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s8s8_s8__3leftn( void )
{
    uint8 Shifted;
    Shifted = Bfx_ShiftBitSat_s8s8_s8( 3, 0xE6 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x30, Shifted, "Value is not 0x30 as supposed to be" );
}

/**
 * @brief   **Test shift to the right 3 bits**
 *
 * The test validates a shift to the right by 3 bits over a variable with value 0x76, to pass Data
 * should be equal to 0x0E.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s8s8_s8__3righp( void )
{
    uint8 Shifted;
    Shifted = Bfx_ShiftBitSat_s8s8_s8( -3, 0x76 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0x0E, Shifted, "Value is not 0x0E as supposed to be" );
}

/**
 * @brief   **Test negative shift to the right 3 bits**
 *
 * The test validates a shift to the right by 3 bits over a signed variable with value 0xE6, to pass Data
 * should be equal to 0xFC.
 * 
 * @test    SWS_Bfx_91002, SWS_Bfx_00134, SWS_Bfx_00135
 */
void test__Bfx_ShiftBitSat_s8s8_s8__3righn( void )
{
    uint8 Shifted;
    Shifted = Bfx_ShiftBitSat_s8s8_s8( -3, 0xE6 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 0xFC, Shifted, "Value is not 0xFC as supposed to be" );
}

/**
 * @brief   **Test count 3 ones**
 *
 * The test validates if the three most significant bits are one over a varible with value 0xE6,
 * to pass Ones should be equal to 3.
 * 
 * @test    SWS_Bfx_91003, SWS_Bfx_00137
 */
void test__Bfx_CountLeadingOnes_u8__3ones( void )
{
    uint8 Ones;
    Ones = Bfx_CountLeadingOnes_u8( 0xE6 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 3, Ones, "Value is not 3 as supposed to be" );
}

/**
 * @brief   **Test signed count 2 ones**
 *
 * The test validates if the two most significant bits are one over a signed varible with value 0xE6,
 * to pass Bits should be equal to 2.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s8__2ones( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s8( 0xE6 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 2, Bits, "Value is not 2 as supposed to be" );
}

/**
 * @brief   **Test signed count 4 zeroes**
 *
 * The test validates if the four most significant bits are zero over a signed varible with value 0x06,
 * to pass Bits should be equal to 4.
 * 
 * @test    SWS_Bfx_91004, SWS_Bfx_00139
 */
void test__Bfx_CountLeadingSigns_s8__4zeroes( void )
{
    uint8 Bits;
    Bits = Bfx_CountLeadingSigns_s8( 0x06 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 4, Bits, "Value is not 4 as supposed to be" );
}

/**
 * @brief   **Test count 3 zeroes**
 *
 * The test validates if the three most significant bits are zero over a varible with value 0x16,
 * to pass Zeroes should be equal to 3.
 * 
 * @test    SWS_Bfx_91005, SWS_Bfx_00141
 */
void test__Bfx_CountLeadingZeros_u8__3zeroes( void )
{
    uint8 Zeroes;
    Zeroes = Bfx_CountLeadingZeros_u8( 0x16 );
    TEST_ASSERT_EQUAL_HEX8_MESSAGE( 3, Zeroes, "Value is not 3 as supposed to be" );
}
