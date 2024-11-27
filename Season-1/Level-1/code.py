'''
Welcome to Secure Code Game Season-1/Level-1!

Follow the instructions below to get started:

1. tests.py is passing but code.py is vulnerable
2. Review the code. Can you spot the bug?
3. Fix the code but ensure that tests.py passes
4. Run hack.py and if passing then CONGRATS!
5. If stuck then read the hint
6. Compare your solution with solution.py
'''

from collections import namedtuple

Order = namedtuple('Order', 'id, items')
Item = namedtuple('Item', 'type, description, amount, quantity')

MAX_PRODUCT_AMOUNT = 10_000_000  # Example threshold in cents for product totals.

def validorder(order: Order):
    net = 0
    product_total = 0  # Track product totals for separate threshold enforcement.

    for item in order.items:
        if item.type == 'payment':
            net += int(round(item.amount * 100))  # Convert to cents
        elif item.type == 'product':
            product_amount = int(round(item.amount * 100 * item.quantity))  # Convert to cents
            product_total += product_amount
            net -= product_amount
        else:
            return "Invalid item type: %s" % item.type

        # Check if product totals exceed the maximum allowable amount
        if product_total > MAX_PRODUCT_AMOUNT:
            return "Total amount payable for an order exceeded"

    if net != 0:
        return "Order ID: %s - Payment imbalance: $%0.2f" % (order.id, net / 100.0)  # Convert back to dollars
    else:
        return "Order ID: %s - Full payment received!" % order.id

