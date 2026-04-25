---
layout: home
author_profile: true
---

Welcome to my site!
{% assign all_projects = site.projectsgis | concat: site.projectsarduino | sort: "date" | reverse %}

{% for project in all_projects limit: 5 %}
  <div>
    <a href="{{ project.url }}">{{ project.title }}</a>
    <p>{{ project.excerpt }}</p>
  </div>
{% endfor %}
