#include "gpio.h"

#define GPIO_MODE_MAX        0x04
#define GPIO_OUTPUT_TYPE_MAX 0x03
#define GPIO_SPEED_MAX       0x04
#define GPIO_PUPD_MAX        0x03
#define GPIO_PIN_MAX         16

void assert_failed(void)
{
  while(1);
}

void ok(void)
{
  __asm("NOP");
}

#define __assert(exp) ((exp) ? ok() : assert_failed())

#define IS_A_ALL_INSTANCE(INSTANCE)   (((INSTANCE)== GPIOA) ||\
                                       ((INSTANCE)== GPIOB)||\
                                       ((INSTANCE)== GPIOC)||\
                                       ((INSTANCE)== GPIOD))

/** 
 * Configures the mode of a specific GPIO pin. 
 * The mode determines the function of the pin (e.g., input, output, alternate function, analog).
 * @param GPIOx: The GPIO port to which the pin belongs.
 * @param GPIO_Pin: The specific pin on the GPIO port to configure.
 * @param mode: The mode to set for the pin (e.g., GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG).
 */

static void gpio_PinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t mode)
{
  __assert(mode <= GPIO_MODE_MAX);
  __assert(GPIO_Pin < GPIO_PIN_MAX);
  GPIOx->MODER |= (mode << (2 * GPIO_Pin));
}

/** 
 * Configures the output type of a specific GPIO pin. 
 * The output type determines whether the pin is set as push-pull or open-drain.
 * @param GPIOx: The GPIO port to which the pin belongs.
 * @param GPIO_Pin: The specific pin on the GPIO port to configure.
 * @param output_type: The output type to set (e.g., GPIO_OTYPE_PP for push-pull, GPIO_OTYPE_OD for open-drain).
 */

static void GPIO_output_type(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t output_type)
{
  __assert(output_type < GPIO_OUTPUT_TYPE_MAX);
  GPIOx->OTYPER |= ( output_type << GPIO_Pin);      
}

/** 
 * Configures the speed of a specific GPIO pin. 
 * The speed determines the rate at which the pin can change state.
 * @param GPIOx: The GPIO port to which the pin belongs.
 * @param GPIO_Pin: The specific pin on the GPIO port to configure.
 * @param speed: The speed setting to apply (e.g., GPIO_SPEED_LOW, GPIO_SPEED_MEDIUM, GPIO_SPEED_HIGH).
 */

static void GPIO_speed(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t speed)
{
  __assert(speed <= GPIO_SPEED_MAX);
  GPIOx->OSPEEDR |= (speed << (2 * GPIO_Pin));
}

/** 
 * Configures the pull-up/pull-down resistors for a specific GPIO pin.
 * The pull-up or pull-down resistors are used to set the default state of the pin when it's not actively driven.
 * @param GPIOx: The GPIO port to which the pin belongs.
 * @param GPIO_Pin: The specific pin on the GPIO port to configure.
 * @param pupd: The pull-up/pull-down configuration (e.g., GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN).
 */

static void GPIO_pupd(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t pupd)
{
  __assert(pupd <= GPIO_PUPD_MAX);
  GPIOx->PUPDR |= (pupd << (2 * GPIO_Pin));	
}

 /** 
 * GPIO initialization function 
 * Initializes a GPIO port (GPIOx) and configures the pin settings (gpio_pinConfig) 
 * according to the provided configuration.
 * It sets up the GPIO pin mode, speed, and other settings based on the configuration structure.
 */
    
void GPIO_init(GPIO_TypeDef *GPIOx, GPIO_PinConf_TypeDef * gpio_pinConfig)
{
  __assert(IS_A_ALL_INSTANCE(GPIOx));
  
  gpio_PinMode(GPIOx,gpio_pinConfig->pin, gpio_pinConfig->mode);
  GPIO_output_type(GPIOx,gpio_pinConfig->pin , gpio_pinConfig->output_type);
  GPIO_speed(GPIOx, gpio_pinConfig->pin, gpio_pinConfig->speed);
  GPIO_pupd(GPIOx,gpio_pinConfig->pin, gpio_pinConfig->pull);

}

/** 
 * GPIO pin read function 
 * Reads the current state of a specific GPIO pin (GPIO_Pin) on the given GPIO port (GPIOx). 
 * Returns the value of the pin: 0 for low, 1 for high.
 */

uint8_t GPIO_readPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  unsigned  char bitstatus = 0x00;
  
  if (((GPIOx->IDR) & GPIO_Pin) != 0x00)
  {
    bitstatus = 0x01;
  }
  else
  {
    bitstatus = 0x00;
  }
  return bitstatus;
}

/** 
 * GPIO pin write function 
 * Writes a value (0 or 1) to a specific GPIO pin (GPIO_Pin) on the given GPIO port (GPIOx). 
 * This function controls the state of the pin: setting it high (1) or low (0).
 */

void GPIO_writePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t val)
{
 if (val !=0x0)
  {
    GPIOx->ODR |= GPIO_Pin;
  }
  else
  {
    GPIOx->ODR &= (~GPIO_Pin);
  }
}
