#include <stm32f10x_conf.h>



void TIM4_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
        {
            // Обязательно сбрасываем флаг
            TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
            GPIOA->ODR ^= GPIO_Pin_1;
        }
}

int main(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* Initialize LED which connected to PC13 */
    GPIO_InitTypeDef  gpio;
    // Enable PORTC Clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    /* Configure the GPIO_LED pin */
    gpio.GPIO_Pin = GPIO_Pin_1;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

   GPIO_ResetBits(GPIOA, GPIO_Pin_1);

    // TIMER4
    TIM_TimeBaseInitTypeDef Timer;
    NVIC_InitTypeDef nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseStructInit(&Timer);
    Timer.TIM_CounterMode = TIM_CounterMode_Up;
    Timer.TIM_Prescaler =8000;
    Timer.TIM_Period = 2000;
    TIM_TimeBaseInit(TIM4, &Timer);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    /* NVIC Configuration */
    /* Enable the TIM4_IRQn Interrupt */
    nvic.NVIC_IRQChannel = TIM4_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    while(1)
    {
    }
}
