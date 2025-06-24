/*********************************************************************************

Copyright(c) 2013-2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

/** @addtogroup GPIO_Service GPIO Service
 *  @{
 */

/**
* @file      adi_gpio.h
* @brief     GPIO definitions and API
* @version:  $Revision: 64700 $
* @date:     $Date: 2020-08-21 10:07:34 -0400 (Fri, 21 Aug 2020) $
*
* @details
*            This is the primary header file for the general-purpose input/output (GPIO) 
*            port driver, which contains the API declarations, data and constant definitions
*            used in the APIs
*/

/* disable MISRA diagnostics as necessary */
#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_2_4:"(advisory) Sections of code should not be commented out.")
#endif /* _MISRA_RULES */

#ifndef __ADI_GPIO_H__
#define __ADI_GPIO_H__

#include <sys/platform.h> 
#include <stdint.h>
#include <stdbool.h>

#if !defined(__BYTE_ADDRESSING__) && defined(__ADSPSHARC__)
	#error "Only Byte addressing mode is supported"
#endif 

/* processors with a PINT module */
#if defined(__ADSPBF548_FAMILY__) || defined(__ADSPBF548M_FAMILY__) || \
    defined(__ADSPBF609_FAMILY__) || \
    defined(ADI_ADSP_CM40Z)       || \
    defined(ADI_ADSP_CM41X)       || \
    defined(__ADSPBF707_FAMILY__) || \
    defined(__ADSPBF725W_FAMILY__) || \
    defined(__ADSPSC589_FAMILY__) || \
    defined(__ADSPSC573_FAMILY__) || \
	defined(__ADSP21569_FAMILY__) || \
	defined(__ADSPSC594_FAMILY__)
#include <services/gpio/adi_gpio_pint.h>
#endif

#if defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__)
#include <services/gpio/adi_gpio_pads.h>
#endif

#if defined(__ADSPBF609_FAMILY__)   || \
    defined(ADI_ADSP_CM40Z)         || \
    defined(ADI_ADSP_CM41X)         || \
    defined(__ADSPBF707_FAMILY__)   || \
    defined(__ADSPBF725W_FAMILY__)   || \
    defined(__ADSPSC589_FAMILY__)   || \
    defined(__ADSPSC573_FAMILY__)	|| \
	defined(__ADSP21569_FAMILY__)   || \
	defined(__ADSPSC594_FAMILY__)

#define	ADI_GPIO_PIN_31   (0x80000000u)          /* Configure GPIO Pin 31. */
#define	ADI_GPIO_PIN_30   (0x40000000u)          /* Configure GPIO Pin 30. */
#define	ADI_GPIO_PIN_29   (0x20000000u)          /* Configure GPIO Pin 29. */
#define	ADI_GPIO_PIN_28   (0x10000000u)          /* Configure GPIO Pin 28. */
#define	ADI_GPIO_PIN_27   (0x08000000u)          /* Configure GPIO Pin 27. */
#define	ADI_GPIO_PIN_26   (0x04000000u)          /* Configure GPIO Pin 26. */
#define	ADI_GPIO_PIN_25   (0x02000000u)          /* Configure GPIO Pin 25.  */
#define	ADI_GPIO_PIN_24   (0x01000000u)          /* Configure GPIO Pin 24.  */
#define	ADI_GPIO_PIN_23   (0x00800000u)          /* Configure GPIO Pin 23.  */
#define	ADI_GPIO_PIN_22   (0x00400000u)          /* Configure GPIO Pin 22.  */
#define	ADI_GPIO_PIN_21   (0x00200000u)          /* Configure GPIO Pin 21.  */
#define	ADI_GPIO_PIN_20   (0x00100000u)          /* Configure GPIO Pin 20.  */
#define	ADI_GPIO_PIN_19   (0x00080000u)          /* Configure GPIO Pin 19.  */
#define	ADI_GPIO_PIN_18   (0x00040000u)          /* Configure GPIO Pin 18.  */
#define	ADI_GPIO_PIN_17   (0x00020000u)          /* Configure GPIO Pin 17.  */
#define	ADI_GPIO_PIN_16   (0x00010000u)          /* Configure GPIO Pin 16.  */

#define	ADI_GPIO_LOCK_FER   (0x00000001u)        /* Configure LOCK_FER bit */
#define	ADI_GPIO_LOCK_MUX   (0x00000002u)        /* Configure LOCK_MUX bit */
#define	ADI_GPIO_LOCK_DATA  (0x00000004u)        /* Configure LOCK_DATA bit */
#define	ADI_GPIO_LOCK_DIR   (0x00000008u)        /* Configure LOCK_DIR bit */
#define	ADI_GPIO_LOCK_INEN  (0x00000010u)        /* Configure LOCK_INEN bit */
#define	ADI_GPIO_LOCK_POLAR (0x00000020u)        /* Configure LOCK_POLAR bit */
#define	ADI_GPIO_LOCK_LOCK  (0x80000000u)        /* Configure LOCK_LOCK bit */
#endif

#define	ADI_GPIO_PIN_15   (0x00008000u)          /* Configure GPIO Pin 15. */
#define	ADI_GPIO_PIN_14   (0x00004000u)          /* Configure GPIO Pin 14. */
#define	ADI_GPIO_PIN_13   (0x00002000u)          /* Configure GPIO Pin 13. */
#define	ADI_GPIO_PIN_12   (0x00001000u)          /* Configure GPIO Pin 12. */
#define	ADI_GPIO_PIN_11   (0x00000800u)          /* Configure GPIO Pin 11. */
#define	ADI_GPIO_PIN_10   (0x00000400u)          /* Configure GPIO Pin 10. */
#define	ADI_GPIO_PIN_9    (0x00000200u)          /* Configure GPIO Pin 9.  */
#define	ADI_GPIO_PIN_8    (0x00000100u)          /* Configure GPIO Pin 8.  */
#define	ADI_GPIO_PIN_7    (0x00000080u)          /* Configure GPIO Pin 7.  */
#define	ADI_GPIO_PIN_6    (0x00000040u)          /* Configure GPIO Pin 6.  */
#define	ADI_GPIO_PIN_5    (0x00000020u)          /* Configure GPIO Pin 5.  */
#define	ADI_GPIO_PIN_4    (0x00000010u)          /* Configure GPIO Pin 4.  */
#define	ADI_GPIO_PIN_3    (0x00000008u)          /* Configure GPIO Pin 3.  */
#define	ADI_GPIO_PIN_2    (0x00000004u)          /* Configure GPIO Pin 2.  */
#define	ADI_GPIO_PIN_1    (0x00000002u)          /* Configure GPIO Pin 1.  */
#define	ADI_GPIO_PIN_0    (0x00000001u)          /* Configure GPIO Pin 0.  */

/** The amount of application memory needed per callback. */
#define ADI_GPIO_CALLBACK_MEM_SIZE (16u)

/**
 * Enumeration of result codes generated by GPIO driver.
 *
 *  These return codes may have different meaning with respect to different
 *  API. Please refer the description of each API for the description of the
 *  return codes with respect to that particular API.
 *
 */
typedef enum
{
    ADI_GPIO_SUCCESS = 0,              /*!< The API call succeeded. */
    ADI_GPIO_FAILURE,                  /*!< The API call failed. */
    ADI_GPIO_INVALID_PORT,             /*!< The port parameter is invalid. */
    ADI_GPIO_INVALID_PIN,              /*!< The pin parameter is invalid. */
    ADI_GPIO_INVALID_DIRECTION,        /*!< The direction parameter is invalid. */
    ADI_GPIO_INVALID_TRIGGER,          /*!< The trigger parameter is invalid. */
    ADI_GPIO_INVALID_EDGE_SENSE,       /*!< The edge sense parameter is invalid. */
    ADI_GPIO_INVALID_MASK,             /*!< The interrupt mask is invalid. */
    ADI_GPIO_INVALID_PIN_INTERRUPT,    /*!< The pin interrupt parameter is invalid. */
    ADI_GPIO_INVALID_PIN_BYTE,         /*!< The pin interrupt channel byte is invalid. */
    ADI_GPIO_INVALID_PIN_PORT,         /*!< The half port register is invalid. */
    ADI_GPIO_INVALID_MEMORY,           /*!< The memory pointer is invalid */
    ADI_GPIO_CALLBACK_MEMORY_FULL,     /*!< The callback memory is full */
    ADI_GPIO_CALLBACK_INVALID,         /*!< The callback parameter is invalid */
    ADI_GPIO_CALLBACK_NOT_FOUND,       /*!< The callback entry is not found */
    ADI_GPIO_NOT_SUPPORTED             /*!< The API is not supported for the processor type. */
} ADI_GPIO_RESULT;

/**
 * The GPIO direction enumerations.
 */
typedef enum
{
    ADI_GPIO_DIRECTION_INPUT,          /*!< Set the GPIO pin to an input. */
    ADI_GPIO_DIRECTION_OUTPUT          /*!< Set the GPIO pin to an output. */
    
} ADI_GPIO_DIRECTION;

/**
 * The GPIO edge sense enumerations.
 */
typedef enum
{
    ADI_GPIO_SENSE_LEVEL_HIGH,               /*!< Generate interrupt when level high on pin. */
    ADI_GPIO_SENSE_LEVEL_LOW,                /*!< Generate interrupt when level low on pin. */
    ADI_GPIO_SENSE_RISING_EDGE,              /*!< Generate interrupt on rising edge. */
    ADI_GPIO_SENSE_FALLING_EDGE,             /*!< Generate interrupt on falling edge. */
    ADI_GPIO_SENSE_BOTH_EDGES                /*!< Generate interrupt on both rising and falling edges. */
    
} ADI_GPIO_SENSE;

#if !defined(__ADI_GPIO_HAS_PINT__)

#if defined(__ADSPBF561_FAMILY__)
/**
 * The GPIO port enumerations (__ADSPBF561_FAMILY__).
 */
typedef enum
{
    ADI_GPIO_PORT_F0,                 /*!< Configure GPIO port PF0-PF15. */
    ADI_GPIO_PORT_F1,                 /*!< Configure GPIO port PF16-PF31. */
    ADI_GPIO_PORT_F2                  /*!< Configure GPIO port PF32-PF47. */

} ADI_GPIO_PORT;
#define NUM_GPIO_PORTS (3)

#elif defined(__ADSPBF533_FAMILY__)
/**
 * The GPIO port enumerations (__ADSPBF533_FAMILY__).
 */
typedef enum
{
    ADI_GPIO_PORT_F                    /*!< Configure GPIO port F. */

} ADI_GPIO_PORT;
#define NUM_GPIO_PORTS (1)

#elif defined(__ADSPBF538_FAMILY__)
/**
 * The GPIO port enumerations (__ADSPBF538_FAMILY__)
 */
typedef enum
{
    ADI_GPIO_PORT_C,                   /*!< Configure GPIO port C. */
    ADI_GPIO_PORT_D,                   /*!< Configure GPIO port D. */
    ADI_GPIO_PORT_E,                   /*!< Configure GPIO port E. */
    ADI_GPIO_PORT_F                    /*!< Configure GPIO port F. */

} ADI_GPIO_PORT;
#define NUM_GPIO_PORTS (4)

#elif defined(__ADSPBF592_FAMILY__)
/**
 * The GPIO port enumerations (__ADSPBF592_FAMILY__).
 */
typedef enum
{
    ADI_GPIO_PORT_F,                   /*!< Configure GPIO port F. */
    ADI_GPIO_PORT_G                    /*!< Configure GPIO port G. */

} ADI_GPIO_PORT;
#define NUM_GPIO_PORTS (2)

#else
/**
 * The GPIO port enumerations.
 */
typedef enum
{
    ADI_GPIO_PORT_F,                   /*!< Configure GPIO port F. */
    ADI_GPIO_PORT_G,                   /*!< Configure GPIO port G. */
    ADI_GPIO_PORT_H                    /*!< Configure GPIO port H. */

} ADI_GPIO_PORT;
#define NUM_GPIO_PORTS (3)
#endif

#endif /* __ADI_GPIO_HAS_PINT__ */

#if !(defined(__ADSP21569_FAMILY__)|| defined(__ADSPSC594_FAMILY__))
/**
 * The GPIO interrupt channel enumerations.
 */
typedef enum
{
    ADI_GPIO_MASK_A,                        /*!< Configure GPIO mask channel A. */
    ADI_GPIO_MASK_B                         /*!< Configure GPIO mask channel B. */

} ADI_GPIO_INTERRUPT_CHANNEL;

/**
 * The GPIO hysteresis enumerations.
 */
typedef enum
{
	ADI_GPIO_HYSTERESIS_GROUP_0,     /*!< Configure group 0 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_1,     /*!< Configure group 1 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_2,     /*!< Configure group 2 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_3,     /*!< Configure group 3 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_4,     /*!< Configure group 4 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_5,     /*!< Configure group 5 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_6,     /*!< Configure group 6 hysteresis. */
	ADI_GPIO_HYSTERESIS_GROUP_7      /*!< Configure group 7 hysteresis. */
} ADI_GPIO_HYSTERESIS_GROUP;

/**
 * The PADS_PORT enumeration.
 */
typedef enum
{
	ADI_GPIO_PADS_PORTA      = 0x0001u,
	ADI_GPIO_PADS_PORTB      = 0x0002u,
	ADI_GPIO_PADS_PORTC      = 0x0004u,
	ADI_GPIO_PADS_PORTD      = 0x0008u,
	ADI_GPIO_PADS_PORTE      = 0x0010u,
	ADI_GPIO_PADS_PORTF      = 0x0020u,
	ADI_GPIO_PADS_PORTG      = 0x0040u
} ADI_GPIO_PADS_PORT;

/**
 * The PADS_NONPORT enumeration.
 */
typedef enum
{
	ADI_GPIO_PADS_CLKOUT     = 0x0001u,
	ADI_GPIO_PADS_ASYNC      = 0x0002u
} ADI_GPIO_PADS_NONPORT;

/**
 * The PADS_PORTS_DS register enumeration.
 */
typedef enum
{
	ADI_GPIO_DS_9_LEGS       = 0x0u,
	ADI_GPIO_DS_7_LEGS       = 0x1u,
	ADI_GPIO_DS_5_LEGS       = 0x2u,
	ADI_GPIO_DS_3_LEGS       = 0x3u
} ADI_GPIO_DRIVE_STRENGTH;


#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ADI_DEBUG
bool ValidatePort(ADI_GPIO_PORT port);  /* Function Declaration for ValidatePort() */
#endif

/*
 * The GPIO API functions.
 */

/**
 * Initialize GPIO
 */
ADI_GPIO_RESULT adi_gpio_Init(
		void *const             pDeviceMemory,
		uint32_t                nMemorySize,
		uint32_t				*pMaxCallbacks
);

/**
 * Set the GPIO direction.
 */
ADI_GPIO_RESULT adi_gpio_SetDirection(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Pins,
    ADI_GPIO_DIRECTION  const eDirection
);

/**
 * Sets the given GPIO pin(s) to a logic high level.  Value of other pins are not affected.
 *
 */
ADI_GPIO_RESULT adi_gpio_Set(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Pins
);

/**
 * Sets the given GPIO pin(s) to a logic low level.  Value of other pins are not affected.
 *
 */
ADI_GPIO_RESULT adi_gpio_Clear(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Pins
);

/**
 * Toggle the logic level of the given GPIO pin(s).  Value of other pins are not affected.
 *
 */
ADI_GPIO_RESULT adi_gpio_Toggle(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Pins
);

/**
 * Get the logic level of the given GPIO Pins(s) on the given port
 *
 */
ADI_GPIO_RESULT adi_gpio_GetData(
    ADI_GPIO_PORT       const ePort,
    uint32_t                 *pValue);

#if defined(__ADSPBF609_FAMILY__) || \
    defined(ADI_ADSP_CM40Z)       || \
    defined(ADI_ADSP_CM41X)       || \
    defined(__ADSPBF707_FAMILY__) || \
    defined(__ADSPBF725W_FAMILY__) || \
    defined(__ADSPSC589_FAMILY__) || \
    defined(__ADSPSC573_FAMILY__) || \
	defined(__ADSP21569_FAMILY__) || \
	defined(__ADSPSC594_FAMILY__)
/**
 * Enable or disable inversion on the given GPIO Pins(s) on the given port.
 *
 */
ADI_GPIO_RESULT adi_gpio_EnablePolar(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Pins,
    bool                const bEnable
);

/**
 * Enable or disable port lock controls
 */
ADI_GPIO_RESULT adi_gpio_EnableLock(
    ADI_GPIO_PORT       const ePort,
    uint32_t            const Lock,
    bool                const bEnable
);

/**
 * Get the module version.
 */
ADI_GPIO_RESULT adi_gpio_GetRevision(
    ADI_GPIO_PORT       const ePort,
    uint32_t                 *pValue);

#if defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__)
/**
 * Toggle the logic level of the given GPIO pin(s) on trigger.  Value of other pins are not affected.
 *
 */
ADI_GPIO_RESULT adi_gpio_TriggerToggle(
	ADI_GPIO_PORT  const ePort,
	uint32_t   const Pins);

/**
 * Sets the given mode of GPIO pin(s). Value of other pins are not affected.
 *
 */
ADI_GPIO_RESULT adi_gpio_PortInit(
	ADI_GPIO_PORT const ePort,
	uint32_t  const Pins,
	ADI_GPIO_DIRECTION const eDirection,
	bool bEnable);

#endif

#if defined(__ADSPBF609_FAMILY__)
/**
 * Enable or disable port hysteresis
 */
ADI_GPIO_RESULT adi_gpio_EnableInputHysteresis(
    uint32_t            const Ports,
    bool                const bEnable
);
#endif

#endif

#if !defined(__ADI_GPIO_HAS_PINT__)

/**
 * GPIO callback function signature
 */
typedef void (* ADI_GPIO_CALLBACK) (
    ADI_GPIO_PORT    ePort,
    uint32_t         Data,
    void*            pCBParam);

/**
 * Set the given GPIO pin(s) input edge sensitivity.
 */
ADI_GPIO_RESULT adi_gpio_SetInputEdgeSense(
    ADI_GPIO_PORT         const ePort,
    uint32_t              const Pins,
    ADI_GPIO_SENSE        const eSense
);

/**
 * Enable or disable input hysteresis for the given GPIO pin(s).
 */
ADI_GPIO_RESULT adi_gpio_EnableInputHysteresis(
    ADI_GPIO_PORT               const ePort,
    ADI_GPIO_HYSTERESIS_GROUP   const ePinGroup,
    bool                        const bEnable
);

/**
 * Enable or disable the interrupt mask for the given GPIO pin(s)
 */
ADI_GPIO_RESULT adi_gpio_EnableInterruptMask(
    ADI_GPIO_PORT              const ePort,
    uint32_t                   const Pins,
    ADI_GPIO_INTERRUPT_CHANNEL const Channel,
    bool                       const bEnable
);

/**
 * Register a user callback function for the given GPIO port.
 */
ADI_GPIO_RESULT adi_gpio_RegisterCallback(
    ADI_GPIO_PORT            const ePort,
    uint32_t                 const Pins,
    ADI_GPIO_CALLBACK        const pfCallback,
    void *                   const pCBParam
);

/**
 * Remove a user callback function for the given GPIO port.
 */
ADI_GPIO_RESULT adi_gpio_UnRegisterCallback(
    ADI_GPIO_PORT            const ePort,
    uint32_t                 const Pins,
    ADI_GPIO_CALLBACK        const pfCallback
);

#else

/* Processors with a PINT module */

/**
 * Interrupt callback function signature
 */
typedef void (* ADI_GPIO_CALLBACK) (
    ADI_GPIO_PIN_INTERRUPT   const ePinInt,
    uint32_t                 const Data,
    void*                    pCBParam);

/**
 * Assign port pin(s) to a pin interrupt channel.
 */
ADI_GPIO_RESULT adi_gpio_PinInterruptAssignment(
    ADI_GPIO_PIN_INTERRUPT   const ePinInt,
    ADI_GPIO_PIN_ASSIGN_BYTE const eByte,
    ADI_GPIO_PIN_ASSIGN_PORT const ePort
);

/**
 * Enable or disable a pin interrupt.
 */
ADI_GPIO_RESULT adi_gpio_EnablePinInterruptMask(
    ADI_GPIO_PIN_INTERRUPT   const ePinInt,
    uint32_t                 const Pins,
    bool                     const bEnable
);

/**
 * Set the given interrupt pin(s) input edge sensitivity.
 */
ADI_GPIO_RESULT adi_gpio_SetPinIntEdgeSense(
    ADI_GPIO_PIN_INTERRUPT   const ePinInt,
    uint32_t                 const Pins,
    ADI_GPIO_SENSE           const eSense
);

/**
 * Get the logic level of the given pins(s) on the given interrupt channel
 */
ADI_GPIO_RESULT adi_gpio_GetPinInterruptState(
    ADI_GPIO_PIN_INTERRUPT   const ePinInt,
    uint32_t                       *pValue
);

/**
 * Register a user callback function for the given GPIO port.
 */
ADI_GPIO_RESULT adi_gpio_RegisterCallback(
    ADI_GPIO_PIN_INTERRUPT     const ePinInt,
    uint32_t                   const Pins,
    ADI_GPIO_CALLBACK          const pfCallback,
    void *                     const pCBParam
);

/**
 * Remove a user callback function for the given GPIO port.
 */
ADI_GPIO_RESULT adi_gpio_UnRegisterCallback(
    ADI_GPIO_PIN_INTERRUPT     const ePinInt,
    uint32_t                   const Pins,
    ADI_GPIO_CALLBACK          const pfCallback
);

#if defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__)
/**
 * Interrupt conditions
 */
ADI_GPIO_RESULT adi_gpio_PinInt(ADI_GPIO_PIN_ASSIGN_PORT const ePort,
								uint32_t                 const Pins,
								ADI_GPIO_PIN_INTERRUPT   const ePinInt,
		 						ADI_GPIO_PIN_ASSIGN_BYTE const eByte,
								bool 					 const bMask,
	    						ADI_GPIO_SENSE           const eSense);

/**
 * Configures the PADS_CFG register to enable or disable the control bits
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_Config(ADI_GPIO_PADS_CFG eCfg, bool bEnable);

/**
 * Enables or disables pull up of GPIO pin(s)
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_PortPullup(ADI_GPIO_PORT ePort,
									uint32_t  const Pins,
									bool bEnable);

/**
 * Enables or disables pull down of GPIO pin(s)
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_PortPullDown(ADI_GPIO_PORT ePort,
									uint32_t  const Pins,
									bool bEnable);

/**
 * Configures drive strength of GPIO pin(s) to the valid configurations
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_PortDriveStrength(ADI_GPIO_PORT ePort,
									   uint32_t  const Pins,
									   ADI_GPIO_PADS_DRIVE_STRENGTH eDriveStrength);
/**
 * Enables or disables pull up of DAI pin(s)
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_DAIPullup(uint8_t  cDeviceNo,
								   uint32_t const Pins,
								   bool bEnable);

/**
 * Enables or disables pull down of DAI pin(s)
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_DAIPullDown(uint8_t  cDeviceNo,
								   uint32_t const Pins,
								   bool bEnable);

/**
 * Configures drive strength of DAI pin(s) to the valid configurations
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_DAIDriveStrength(uint8_t  cDeviceNo,
									   uint32_t  const Pins,
									   ADI_GPIO_PADS_DRIVE_STRENGTH eDriveStrength);

/**
 * Enable or disable the control bits in the NONPORTS_CTL register
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_NonPortControl(ADI_GPIO_PADS_NONPORTS_CFG eCfg, bool bEnable);

/**
 * Configures drive strength of non port pin(s) to the valid configurations
 *
 */
ADI_GPIO_PADS_RESULT adi_pads_NonPortDriveStrength( ADI_GPIO_PADS_NONPORTS eNonPort,
													ADI_GPIO_PADS_DRIVE_STRENGTH eDriveStrength);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* __ADI_GPIO_H__ */

/*@}*/

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */
