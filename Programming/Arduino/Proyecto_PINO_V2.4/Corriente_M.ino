// void corriente_m(){
//   currentpg = getCorrientepg(SAMPLESNUMBER);
//    currentRMS = 0.707 * currentpg;
//    power = 230.0 * currentRMS;
//    corrientepg=(currentRMS+currentpg)/2; //Corriente puerta grande
   
//    currentpch = getCorrientepch(SAMPLESNUMBER);
//    currentRMSpg = 0.707 * currentpch;
//    powerpg = 230.0 * currentRMSpg;
//    corrientepch=(currentRMSpg+currentpch)/2; //Corriente puerta chica
// }

// float getCorrientepg(int samplesNumber)
// {
//    float voltage;
//    float corrienteSum = 0;
//    for (int i = 0; i < samplesNumber; i++)
//    {
//       voltage = analogRead(A0) * 5.0 / 1023.0;
//       corrienteSum += (voltage - 2.5) / SENSIBILITY;
//    }
//    return(corrienteSum / samplesNumber);
// }

// float getCorrientepch(int samplesNumber)
// {
//    float voltagepg;
//    float corrienteSumpg = 0;
//    for (int i = 0; i < samplesNumber; i++)
//    {
//       voltagepg = analogRead(A1) * 5.0 / 1023.0;
//       corrienteSumpg += (voltagepg - 2.5) / SENSIBILITY;
//    }
//    return(corrienteSumpg / samplesNumber);
// }
