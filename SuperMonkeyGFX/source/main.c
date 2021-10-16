#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "eGFX_Driver_ST7789_240_240_BD.h"
#include "eGFX.h"
#include "fsl_usart.h"
#include "Sprites_16BPP_RGB565.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_BOARD_TEST_LED_PORT BOARD_LED_BLUE_GPIO_PORT
#define APP_BOARD_TEST_LED_PIN  BOARD_LED_BLUE_GPIO_PIN
#define APP_SW_PORT             BOARD_SW2_GPIO_PORT
#define APP_SW_PIN              BOARD_SW2_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}


int main(void)
{
	eGFX_ImagePlane *Next;

   uint32_t port_state = 0;


    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

  // BOARD_InitDebugConsole();


    /* Board pin, clock, debug console init */
    BOARD_InitPins();

    BOARD_BootClockRUN();

    /* Init output LED GPIO. */
    GPIO_PortInit(GPIO, APP_BOARD_TEST_LED_PORT);
    GPIO_PinInit(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, &led_config);
    SystemCoreClockUpdate();

    SysTick_Config(SystemCoreClock / 1000U);

    SysTick_DelayTicks(1000);
    eGFX_InitDriver();
    Next = (eGFX_ImagePlane *)&Sprite_16BPP_RGB565_monkey;


    while (1)
    {

    	GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);


    	eGFX_Blit(&eGFX_BackBuffer[0],
            	          0,
            	          0,
            	          Next);

       	eGFX_Dump(&eGFX_BackBuffer[0]);

    }
}
