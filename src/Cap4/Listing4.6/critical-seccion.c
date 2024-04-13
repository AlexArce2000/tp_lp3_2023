#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* An array of balances in accounts, indexed by account number. */
float* account_balances;

/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT. Return
   0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
   too small. */
int process_transaction(int from_acct, int to_acct, float dollars)
{
    int old_cancel_state;

    /* Check the balance in FROM_ACCT. */
    if (account_balances[from_acct] < dollars)
        return 1; // Saldo insuficiente

    /* Begin critical section. */
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);

    /* Move the money. */
    account_balances[to_acct] += dollars;
    account_balances[from_acct] -= dollars;

    /* End critical section. */
    pthread_setcancelstate(old_cancel_state, NULL);

    return 0;
}

int main()
{
    // Inicializa account_balances con valores apropiados
    int num_accounts = 100; // Número de cuentas
    account_balances = (float*)malloc(num_accounts * sizeof(float));
    if (account_balances == NULL) {
        perror("Error de asignación de memoria");
        return 1;
    }

    // Inicializa los saldos de cuentas (esto es un ejemplo, debes establecer valores adecuados)
    for (int i = 0; i < num_accounts; i++) {
        account_balances[i] = 1000.0; // Saldo inicial de todas las cuentas
    }

    // Ejemplo de transacción
    int from_acct = 0;
    int to_acct = 1;
    float amount = 200.0;

    if (process_transaction(from_acct, to_acct, amount) == 0) {
        printf("Transacción exitosa.\n");
    } else {
        printf("Error: La transacción no pudo completarse.\n");
    }

    // Libera la memoria cuando hayas terminado
    free(account_balances);

    return 0;
}
