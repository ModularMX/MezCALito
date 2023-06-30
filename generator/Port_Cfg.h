#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#define PORT_DEV_ERROR_DETECT           <PortDevErrorDetect>
#define PORT_SET_PIN_DIRECTION_API      <PortSetPinDirectionApi>
#define PORT_SET_PIN_MODE_API           <PortSetPinModeApi>
#define PORT_VERSION_INFO_API           <PortVersionInfoApi>
#define PORT_PIN_NUMBER_OF_PORTS        <n * PortContainer * n * PortPin>

/*pins to use in our application where port is represented by the
most significant nibble and pin by the less isgnificant nibble*/
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>
#define <PortPinSymbolicName>       ( Port_PinType ) 0x<number[PortNumber]><PortPinId>


/*external reference to Port_Config array*/
extern const Port_ConfigType PortConfig[PORT_PIN_NUMBER_OF_PORTS];

#endif /* PORT_CFG_H_ */
