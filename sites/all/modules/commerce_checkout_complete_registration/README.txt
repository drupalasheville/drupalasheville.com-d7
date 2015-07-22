Registration Confirmation for Anonymous checkouts.

Guest customer option to register after complete checkout.

HOW-TO
Create new pane for the "Complete" checkout page.
This pane has 3 settings (for now) : password required (boolean), account creation email notification (boolean) and the text to be displayed for this pane form.
The pane will contain a button form + extra elements as the settings say.
On this pane form submition:
- an user account will be created and set as the current user;
- the order will be assigned to the new user;
- a Rule event will be invoked (with order and user objects);
- the user will be redirected to its order history page.
