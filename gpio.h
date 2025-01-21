
#include <stdint.h>

/* Mode */

#define GPIO_INPUT_MODE         ( (uint32_t)0x00 )
#define GPIO_OUTPUT_MODE        ( (uint32_t)0x01 )
#define GPIO_ALT_FUN_MODE       ( (uint32_t)0x02 )
#define GPIO_ANALOG_MODE        ( (uint32_t)0x03 )

/* typeOutput */

#define GPIO_OUTPUT_TYPE_PUSHPULL   ( (uint32_t)0x00 )         
#define GPIO_OUTPUT_TYPE_OPEN_DRAIN ( (uint32_t)0x01 )

/* GPIO Speed type selection value */

#define GPIO_SPEED_LOW               ( (uint32_t)0x00 )
#define GPIO_SPEED_MEDIUM            ( (uint32_t)0x01 )
#define GPIO_SPEED_HIGH              ( (uint32_t)0x02 )
#define GPIO_SPEED_VERY_HIGH         ( (uint32_t)0x03 )

/* GPIO  pull-up/pull-down values */

#define         GPIO_NO_PUSH_PULL  ((uint32_t)0x00)
#define         GPIO_PULL_UP       ((uint32_t)0x01)
#define         GPIO_PULL_DOWN     ((uint32_t)0x02)

/*GPIOx_BASE_ADD*/

#define         GPIOA_BASE         (uint32_t *)(0x40020000)
#define         GPIOB_BASE         (uint32_t *)(0x40020400)
#define         GPIOC_BASE         (uint32_t *)(0x40020800)
#define         GPIOD_BASE         (uint32_t *)(0x40020C00)
#define         GPIOE_BASE         (uint32_t *)(0x40021000)
#define         GPIOF_BASE         (uint32_t *)(0x40021400)
#define         GPIOG_BASE         (uint32_t *)(0x40021800)
#define         GPIOH_BASE         (uint32_t *)(0x40021C00)
#define         GPIOI_BASE         (uint32_t *)(0x40022000)
#define         GPIOJ_BASE         (uint32_t *)(0x40022400)

#define         GPIOA              ((GPIO_TypeDef*)GPIOA_BASE)
#define         GPIOB              ((GPIO_TypeDef*)GPIOB_BASE)
#define         GPIOC              ((GPIO_TypeDef*)GPIOC_BASE)
#define         GPIOD              ((GPIO_TypeDef*)GPIOD_BASE)

/* GPIO Init structure definition */

#define    GPIO_Pin_0       ((uint16_t)0x0001)  /* Pin 0 selected */
#define    GPIO_Pin_1       ((uint16_t)0x0002)  /* Pin 1 selected */
#define    GPIO_Pin_2       ((uint16_t)0x0004)  /* Pin 2 selected */
#define    GPIO_Pin_3       ((uint16_t)0x0008)  /* Pin 3 selected */
#define    GPIO_Pin_4       ((uint16_t)0x0010)  /* Pin 4 selected */
#define    GPIO_Pin_5       ((uint16_t)0x0020)  /* Pin 5 selected */
#define    GPIO_Pin_6       ((uint16_t)0x0040)  /* Pin 6 selected */
#define    GPIO_Pin_7       ((uint16_t)0x0080)  /* Pin 7 selected */
#define    GPIO_Pin_8       ((uint16_t)0x0100)  /* Pin 8 selected */
#define    GPIO_Pin_9       ((uint16_t)0x0200)  /* Pin 9 selected */
#define    GPIO_Pin_10      ((uint16_t)0x0400)  /* Pin 10 selected */
#define    GPIO_Pin_11      ((uint16_t)0x0800)  /* Pin 11 selected */
#define    GPIO_Pin_12      ((uint16_t)0x1000)  /* Pin 12 selected */
#define    GPIO_Pin_13      ((uint16_t)0x2000)  /* Pin 13 selected */
#define    GPIO_Pin_14      ((uint16_t)0x4000)  /* Pin 14 selected */
#define    GPIO_Pin_15      ((uint16_t)0x8000)  /* Pin 15 selected */

/**
 * @brief GPIO Peripheral Register Definition
 * 
 * This structure represents the memory-mapped registers for GPIO peripherals 
 * on the STM32F407VG microcontroller. Each field corresponds to a specific 
 * register used to configure and control GPIO functionality.
 */
typedef struct {
        volatile uint32_t MODER;   /* GPIO mode register */
        volatile uint32_t OTYPER;  /* GPIO output type register */
        volatile uint32_t OSPEEDR; /* GPIO output speed register */
        volatile uint32_t PUPDR;   /* GPIO pull-up/pull-down register */
        volatile uint32_t IDR;     /* GPIO input data register */
        volatile uint32_t ODR;     /* GPIO output data register */
        volatile uint32_t BSRR;    /* GPIO bit set/reset register */
        volatile uint32_t LCKR;    /* GPIO configuration lock register*/
        volatile uint32_t AFRL;    /* GPIO alternate function low register */
        volatile uint32_t AFRH;    /* GPIO alternate function high register */
} GPIO_TypeDef;

/**
 * @brief GPIO Initialization Structure
 * 
 * This structure is used to configure a GPIO pin on the STM32F407VG.
 * It includes pin number, mode, pull-up/down, speed, and alternate function.
 */

typedef struct{
	uint32_t pin;               /*GPIO pin(s) to configure ( PIN_0 to PIN_15)*/          
	uint32_t mode;              /*Operating mode ( input, output, alternate function)*/
        uint32_t output_type;       /* Output type configuration (push-pull or open-drain) */
	uint32_t pull;              /*Pull-up or pull-down resistor configuration*/
	uint32_t speed;             /*Pin speed ( low, medium, high)*/
	uint32_t alternate;         /*Alternate function (used for peripherals)*/
}GPIO_PinConf_TypeDef;

/* GPIO initialization function */
void GPIO_init(GPIO_TypeDef *GPIOx, GPIO_PinConf_TypeDef *gpio_pinConfig);

/* GPIO pin read function */
uint8_t GPIO_readPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* GPIO pin write function */
void GPIO_writePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t val);
