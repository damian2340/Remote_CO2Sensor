

typedef enum
{
    ReleasedButtonState = 0x00,
    AutoCalButtonState = 0x01,
    ResetButtonState = 0x02,
    CancelButonState = 0x04
} taskButonState_t;

void checkButtonTask();