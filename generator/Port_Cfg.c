const Port_ConfigType PortConfig[PORT_PIN_NUMBER_OF_PORTS]
{
    /*Port A*/
    .moder = <PortPinInitialMode_15> | <PortPinInitialMode_14> | ... | <PortPinInitialMode_0>,  
    .otyper = <PortPinOutputPinDriveMode_15> | <PortPinOutputPinDriveMode_14> | ... | <PortPinOutputPinDriveMode_0>,
    .ospeedr = <PortPinOutputPinSpeed_15> | <PortPinOutputPinSpeed_14> | ... | <PortPinOutputPinSpeed_0>,
    .pupdr = <PortPinInternalResistor_15> | <PortPinInternalResistor_14> | ... | <PortPinInternalResistor_0>,
    .odr = <PortPinLevelValue_15> | <PortPinLevelValue_14> | ... | <PortPinLevelValue_0>,
    .ModeChangeable = <PortPinModeChangeable_15> | <PortPinModeChangeable_14> | ... | <PortPinModeChangeable_0>,
    .DirectionChangeable = <PortPinDirectionChangeable_15> | <PortPinDirectionChangeable_14> | ... | <PortPinDirectionChangeable_0>,

    /*Port B*/

    /*Port C*/
}

  