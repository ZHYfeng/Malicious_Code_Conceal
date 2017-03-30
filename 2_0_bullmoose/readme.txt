Created by Bull Moose:
This is a basic Hyper Text Markup Language File infector that changes a registry key to run this program
insted of iexplore.exe, then appends the infection string (In this case, a Javascript Script) into the file and calls the API ShellExecute() to
Execute the the file by calling iexplore with the parameter of the file. This is merely a proof of concept virus
that demonstrates people that use Microsoft Windows with Internet Explorer are at a great security risk,
especially from Phishing, as this could have easily dropped a Phisher Script into the file then run it.